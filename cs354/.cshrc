# this file is processed on every csh invocation

# set PATH and MANPATH based on machine type (exports to "help" that script)
setenv SHELL csh
export SHELL
eval `/usr/local/bin/defaultpaths`

# set default file/directory creation protection
umask 007

setenv ENTOMB yes

# skip the rest if the shell is non-interactive, i.e. is running a script
if ( ! $?prompt ) exit

set prompt = "`shorthostname` \! % "
set history = 50
set notify = on

alias mail mailx
