#include "transform.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <algorithm>

#include <assembly/catalog.hpp>
#include <assembly/manifest.hpp>
#include <assembly/filesystem.hpp>

#include "sd0_stream.hpp"
#include "md5.h"

extern int verbose_flag;



using namespace assembly::manifest;
using namespace assembly::catalog;

void ConfigTransformStage::run(std::istream* source, std::ostream* sink) {
    //gfxDataStore store;

    std::string get;
    while(std::getline(*source, get, ',')) {
        int index = get.find_first_of('=');
        //gfxValueType type = gfxType(get[index + 1] - '0');
        std::string key = get.substr(0, index);
        std::string value = get.substr(index+3);
        // store.insert(std::make_pair<>(key, toGfxValue(type, value)));
        *sink << std::setw(20) << key << ": " << value << std::endl;
    }
}

void NoTransformStage::run(std::istream* source, std::ostream* sink) {

    char buf[512];
    while (source->read(buf, 512)) {
        sink->write(buf, 512);
    }
    sink->write(buf, source->gcount());

}

void MD5TransformStage::run(std::istream* source, std::ostream* sink) {

    uint SIZE = 2048;
    char buf[SIZE];

    md5_state_t state;
    md5_byte_t digest[16];
    uint64_t size = 0;

    md5_init(&state);
    while (source->read(buf, SIZE)) {
        md5_append(&state, (const md5_byte_t *) buf, SIZE);
        size += SIZE;
    }

    uint add = source->gcount();
    size += add;
    md5_append(&state, (const md5_byte_t *) buf, add);
    md5_finish(&state, digest);

    *sink << std::hex;
    for (int i = 0 ; i < 16; i++)
    {
        *sink << std::setw(2) << std::setfill('0') << (int) digest[i];
    }
    *sink << std::dec << " - " << size << " Bytes" << std::endl;
}

ManifestTransformStage::ManifestTransformStage(std::string base_url) : base_url(base_url)
{

}

void ManifestTransformStage::run(std::istream* source, std::ostream* sink)
{
    manifest_file manifest;
    read_from_stream(*source, manifest);

    if (verbose_flag)
    {
        *sink << std::setw(15) << "FileVersion: " << manifest.fileVersion << std::endl;
        *sink << std::setw(15) << "Checksum: " << manifest.checksum << std::endl;
        *sink << std::setw(15) << "GameVersion: " << manifest.version << std::endl;
        *sink << std::setw(15) << "Files loaded: " << manifest.files.size() << std::endl;
        if (!base_url.empty()) *sink << std::setw(15) << "Base URL: " << base_url << std::endl;
        *sink << std::string(70, '-') << std::endl;
    }

    for (manifest_entry& entry : manifest.files)
    {
        *sink << base_url << entry.checkA[0] << "/" << entry.checkA[1] << "/" << entry.checkA << ".sd0" << std::endl;
    }

    if (verbose_flag)
    {
        *sink << std::string(70, '-') << std::endl;
        *sink << "Done!" << std::endl;
    }
}

void PackIndexTransformStage::run(std::istream* source, std::ostream* sink) {

    catalog_file file;
    read_from_stream(*source, file);

    /* Display pack file entries */
    uint32_t count = file.pack_files.size();

    *sink << std::string(50, '-') << std::endl;
    *sink << std::setw(10) << "Version: " << file.version << std::endl;
    *sink << std::setw(10) << "Files: " << count << std::endl;
    *sink << std::string(50, '-') << std::endl;

    char ind = (char) ceil(log10(count));
    for (int i = 0; i < count; i++)
    {
        // *sink << std::setw(ind) << i << ": " << file.packFiles.at(i) << std::endl;
    }

    /* Display file entries */
    uint32_t count2 = file.files.size();

    *sink << std::string(50, '-') << std::endl;
    *sink << std::setw(10) << "Files: " << count2 << std::endl;
    *sink << std::string(50, '-') << std::endl;

    std::vector<uint32_t> data;

    for (int i = 0; i < count2; i++)
    {
        catalog_entry entry = file.files.at(i);

        if ((entry.data & 1) == 0) {
            uint32_t opt = entry.data >> 8;

            if (std::find(data.begin(), data.end(), opt) == data.end())
            {
                data.push_back(opt);
                *sink << "0x" << std::setw(6) << std::setfill('0') << std::hex << opt << " / ";
                *sink << std::setw(8) << std::setfill(' ') << std::dec << opt << std::endl;

            }
        }
        /*
            *sink << std::setw(9) << entry.crc << " / ";
            *sink << std::setw(5) << entry.left << " / ";
            *sink << std::setw(5) << entry.right << " / ";
            *sink << std::setw(5) << entry.pack << " / ";
            *sink << std::setw(8) << entry.data << " / ";
            *sink << std::endl;
        */
    }
}

void SD0TransformStage::run(std::istream* source, std::ostream* sink) {

    char header[6] = {0,0,0,0,0,0};
    char magic[6] = {'s', 'd', '0', 1, -1, 0};
    source->read((char*) header, 5);

    if (source->eof()) {
        std::cerr << "Header to small" << std::endl;
    }

    if (strcmp(header, magic) != 0) {
        std::cerr << "Header incorrect" << std::endl;
    }

    std::cerr << "FINE" << std::endl;

    uint32_t blocksize;
    uint32_t total = 0;

    source->read((char*) &blocksize, 4);
    while (!source->eof()) {

        std::cerr << "Block[" << blocksize << "]" << std::endl;
        total += blocksize;
        source->seekg(blocksize, std::ios::cur);
        if (source->eof()) return;

        source->read((char*) &blocksize, 4);
    }

    std::cerr << total << std::endl;
}

ClientExtractorStage::ClientExtractorStage(std::string folder) : folder(folder) {}

void ClientExtractorStage::run(std::istream* source, std::ostream* sink) {

    manifest_file manifest;
    read_from_stream(*source, manifest);

    NoTransformStage worker;

    for (manifest_entry& entry : manifest.files) {

        std::string srcpath = this->folder + entry.checkA + ".sd0";
        std::ifstream infile(srcpath);
        if (!infile.is_open())
        {
            std::cerr << "File " << std::setw(35) << srcpath;
            std::cerr << " (" << entry.path << ") not found!" << std::endl;
        }
        else
        {
            std::ofstream outfile(entry.path);
            fs::ensure_dir_exists(entry.path);

            sd0_istreambuf<1024> inflate_buf(&infile);
            std::istream inflated(&inflate_buf);

            worker.run(&inflated, &outfile);

            infile.close();
            outfile.close();
        }
     }
}
