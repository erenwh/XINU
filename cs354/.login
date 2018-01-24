# this file is processed only when csh is running as a login (top-level) shell
# and should contain commands to be run once per session, e.g. setting
# environment variables and terminal-specific settings

setenv EDITOR vi

switch ( `bintype -os` )
case *-linux:
	setenv PAGER less
	# the backspace key sends DEL under Linux
	# readnews is not yet available on Linux
	breaksw
default:
	setenv PAGER more
	stty erase  intr 
	foreach i (purdue.cs.general purdue.cs.labs)
		/p/news/readnews -n $i -l |& sed -ne '/^No news.$/q;p;$s|.*|See news://news/'$i' for details|p'
	end
	biff y
endsw
