#pragma once

int main_pack (int argc, char** argv);
int help_pack(int argc, char** argv);
int test_pack(int argc, char** argv);
int console_pack(int argc, char** argv);

int pack_crc(int argc, char** argv);
int pack_pack_index(int argc, char** argv);
int pack_file_info(int argc, char** argv);
int pack_move_to(int argc, char** argv);
int pack_read_catalog(int argc, char** argv);
int pack_name(int argc, char** argv);

int pack_list(int argc, char** argv);
int pack_tree(int argc, char** argv);
int pack_all(int argc, char** argv);
int pack_missing(int argc, char** argv);
int pack_target(int argc, char** argv);
int pack_full_extract(int argc, char** argv);

int main_catalog(int argc, char** argv);