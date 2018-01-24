# this file is processed only when sh is running as a login (top-level) shell
# and should contain commands to be run once per session, e.g. setting
# environment variables and terminal-specific settings

# set PATH and MANPATH based on machine type
eval `/usr/local/bin/defaultpaths`

# set default file/directory creation protection
umask 007

if [ "${BASH}" ]; then		# we're bash
	[ -f $HOME/.bashrc ] && . $HOME/.bashrc
elif [ `basename "${SHELL}"` = ksh ]; then	# we're ksh
	ENV=$HOME/.kshrc; export ENV
	[ -f $ENV ] && . $ENV
else				# assume good ol' sh
	PS1="`shorthostname` $ "
fi

ENTOMB=yes; export ENTOMB
EDITOR=vi; export EDITOR

case `bintype -os` in
*-linux)
	PAGER=less; export PAGER
	# the backspace key sends DEL under Linux
	# readnews is not yet available on Linux
	;;
*)
	PAGER=more; export PAGER
	stty erase  intr 
	for i in purdue.cs.general purdue.cs.labs; do
		/p/news/readnews -n $i -l 2>&1 | sed -ne '/^No news.$/q;p;$s|.*|See news://news/'$i' for details|p'
	done
	biff y
esac
