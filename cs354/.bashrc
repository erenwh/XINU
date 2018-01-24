# this file is processed on each interactive invocation of bash

PS1="`shorthostname` \! $ "
HISTSIZE=50

alias mail=mailx

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`
export LD_LIBRARY_PATH

