# https://stackoverflow.com/questions/16657803/creating-autocomplete-script-with-sub-commands#16673041

function __fish_prog_needs_command
  set cmd (commandline -opc)
  if [ (count $cmd) -eq 1 -a $cmd[1] = 'paradox' ]
    return 0
  end
  return 1
end

function __fish_prog_using_command
  set cmd (commandline -opc)
  if [ (count $cmd) -gt 1 ]
    if [ $argv[1] = $cmd[2] ]
      return 0
    end
  end
  return 1
end

complete -f -c paradox -n '__fish_prog_needs_command' -a pipe -d 'Stream Processor'
complete -f -c paradox -n '__fish_prog_needs_command' -a catalog -d 'Catalog Reader'
complete -f -c paradox -n '__fish_prog_needs_command' -a pack -d 'Pack-Archiv Utility'
complete -f -c paradox -n '__fish_prog_needs_command' -a fdb -d 'FDB Utility'
complete -f -c paradox -n '__fish_prog_needs_command' -a data -d 'Data Utilities'
complete -f -c paradox -n '__fish_prog_needs_command' -a net -d 'Network Helpers'
complete -f -c paradox -n '__fish_prog_needs_command' -a test -d 'Test Methods'
complete -f -c paradox -n '__fish_prog_needs_command' -a help -d 'Command Overview'

complete -f -c paradox -n '__fish_prog_using_command foo' -a a
complete -f -c paradox -n '__fish_prog_using_command foo' -a b
complete -f -c paradox -n '__fish_prog_using_command foo' -a c
