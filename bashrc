#만일 상호작용하여 실행되지 않는다면 아무것도 하지 않는다.
#$-는 옵션의 현재 설정을 확인할 수 있는 변수로 쉘이 상호작용을 한다면 $i를 포함한다.
#*i*) ;; 는 $- 에 i 가 들어있다면 아무것도 하지 않는다는 의미이며
#*) return;; 은 그 외 나머지 경우 종료하겠다는 의미이다.
case $- in
    *i*) ;;
      *) return;;
esac


#history에서 빈 공간으로 시작되는 라인이나 중복된 라인을 넣지 마라.
#더 많은 옵션을 위해 bash(1)을 확인해라.
#공백으로 시작하는 명령과 연속적으로 중복된 명령을 제거한다.
#HISTCONTROL은 history list 에 어떤 명령어들이 저장되는지 제어하는 값의 list이다.
#- ‘ignorespace’가 포함되어 있으면 공백으로 시작되는 라인을 history list에 저장하지 #않는다.
#- ‘ignoredups’가 포함되어 있으면 직전 line과 같은 line은 저장하지 않는다.
#- 'ignoreboth'는 ‘ignorespace'와 'ignoredups'를 둘 다 설정하는 것이다.
#- ‘erasedups'는 history list에 저장된 모든 line들을 현재의 명령어가 저장되기 전에 비교하고 같은 것들을 지운다.
#- 아무것도 설정되어 있지 않으면 모든 입력 line을 history list에 저장한다.
HISTCONTROL=ignoreboth


#history 파일에 덮에 쓰지 말고 이어붙여라.
#shell option 중 histappend를 설정한다.
#histappend를 설정하면 쉘이 종료될 때 history list를 HISTFILE의 값에 설정된 파일에 덮어쓰지 않고 이어 붙인다.
#HISTFILE은 명령어 history가 저장되는 파일이다. 기본값은 ~/.bash_history 이다.
shopt -s histappend

#history의 길이를 설정하기 위해 bash(1)에서 HISTSIZE와 HISTFILESIZE를 확인해라.
#HISTSIZE는 history list에 기억할 최대 명령어의 수이다. 0으로 설정하면 history list에 어떤 명령어들도 저장되지 않고 음수로 설정하면 입력되는 모든 명령어들을 저장한다.
#HISTFILESIZE는 history file에 포함될 최대 라인의 수로 여기에 설정된 값보다 line의 수가 더 많다면 오래된 것들을 삭제함으로써 HISTFILESIZE에 설정된 값만큼 파일에 저장된 history의 개수를 유지한다.
HISTSIZE=1000
HISTFILESIZE=2000


#각 커맨드 이후에 윈도우 크기를 확인하고 필요하다면
#LiNES 와 COLUMNS의 값을 갱신하라
#checkwinsize 옵션을 설정한다.
#checkwinsize를 설정하면 bash는 각 명령어 이후에 윈도우의 크기를 확인하고 필요하다면 LINE과 COLUMNS의 값을 갱신한다.
shopt -s checkwinsize


#설정했다면, pathname expansion context에 사용된 ** 패턴은
#모든 파일과 0 이나 디렉토리와 서브 디렉토리들은 매칭될 것이다.
#globstar가 설정되면 파일이름에 사용된 ‘**’ 패턴을 모든 파일과 zero, 모든 directory들과 subdirectory를 대조한다. 만약 '**' 패턴이 '/' 다음에 있다면 오직 directory와 subdirectory만을 대조한다.
#shopt -s globstar


#텍스트가 아닌 입력 파일들을 위해 less를 더 친숙하게 만들고, lesspipe(1)을 확인해라.
#eval은 인수들을 하나의 명령어로 결부시키고, 그것은 읽히고 실행되고, 하나로 결부된 명령어의 종료 상태는 eval의 종료 상태로서 반환된다. 즉, 쉘 스크립트파일 안에서 문자열로 표기된 쉘 명령 실행한다.
#/usr/bin/lesspipe가 존재한다면 eval "$(SHELL=/bin/sh lesspipe)"를 실행한다.
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"	


#(프롬프트 아래에서 사용되는) 당신이 작업하고 있는 chroot를 식별하는 변수를 설정해라.
#${parameter:-word} 는 parameter가 설정되지 않았거나 null이면 word의 확장이 대신 쓰인다. 그렇지 않으면 parameter의 값이 대신 쓰인다.
#"${debian_chroot:-}"가 null 이고 /etc/debian_chroot가 읽을 수 있는 파일이면 debian_chroot=$(cat /etc/debian_chroot)를 실행
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi


#화려한 프롬프트를 설정해라(원하는 색을 알고 있는 경우 외에는 색이 없다)
# $TERM 이 xterm-color 이거나 *-256color 라면 color_prompt에 yes를 저장한다.
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac


#만일 터미널에 기능이 있다면 색칠된 프롬프트를 위한 comment를 제거해라.
#사용자의 집중을 흐트리지 않기 위해 기본으로 꺼진다. 
#터미널 윈도우 안에 초점은 프롬프트가 아니라 커맨드의 결과에 있어야한다.
#force_color_prompt=yes
#$force_color_prompt가 null이 아닐 때 if와 fi 사이의 명령어를 실행한다.
#/usr/vin/tput이 실행 가능하면 tput setaf 의 출력을 /dev/null 로 보내 삭제하고
color_prompt를 yes로 설정한다.
if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	#색을 지원한다; 이것은 Ecma-48과 호환한다고 가정한다.
	#(ISO/IEC-6429)(이러한 지원의 부족은 극히 드물고, 그러한 경우에
	#(setaf 보다 setf를 지원하는 경향이 있다.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

# $color_prompt가 yes 가 맞는지 확인하고 조건에 맞게 프롬프트를 설정한다.
#$color_prompt가 yes이면 else 이전까지 실행하고 yes가 아니면 else 이후를 실행한다.
#${parameter:+word}는 parameter가 null 이거나 설정이 되어있지 않으면 어떤 것도 대신하지 않고 그렇지 않으면 word가 대신한다.
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi

#color_prompt와 force_color_prompt를 설정해제한다.
#unset [-fnv] [name]
#unset은 각 변수나 함수 이름을 제거한다. 
#-v 옵션이 주어진다면 name은 쉘 변수를 참조하고, 각 변수는 지워진다.
#-f 옵션이 주어진다면 name은 쉘 함수를 참조하고, 그 함수 정의는 지워진다.
unset color_prompt force_color_prompt


#만일 $TERM이 xterm* 이거나 rxvt*라면 user@host:dir으로 프롬프트를 설정해라.
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac


#ls의 색상 지원을 활성화하고 유용한 별칭을 추가해라
#/usr/bin/dircolors 가 실행 가능하면 아래의 문장들을 실행한다.
#~/.dircolors 가 읽을 수 있는 파일이면 eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"를 실행한다.
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'
    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# GCC의 경고들과 에러들은 색칠된다.
#export GCC_COLORS='error=01;31:warning=01;35:note=01;36:caret=01;32:locus=01:quote=01'

#몇가지 ls의 별칭들
#ll을 입력하면 ls -alF를 실행한다.
#la를 입력하면 ls -A를 실행한다.
#l을 입력하면 ls -CF를 입력한다.
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

#긴 시간 실행하는 명령을 위해 "alert" 별칭을 추가해라
#sleep 10; alert
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

#별칭 정의들.
#그것들을 여기에 바로 추가하는 것 대신에
#~/.bash_aliases와 같은 독립된 파일 안에 당신의 첨가물을 놓길 원할 수도 있다.
#bash-doc 패키지 안의 /usr/share/doc/bash-doc/examples 을 확인해라
#~/.bash_aliases 가 regular file이라면 . ~/.bash_aliases를 실행한다.
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

#프로그래밍이 가능한 특징을 활성화시켜라.
#(만일 /etc/bash.bashrc 와 /etc/profile에서 이미 활성화 되어 있다면 이것을 활성화 시키는 것이 필요하지 않다.
# shopt -op posix 가 거짓이라면 조건을 만족한다.
if ! shopt -oq posix; then
  #/usr/share/bash-completion/bash_completion 가 regular file이면 조건을 만족한다.
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion
  # /usr/share/bash-completion/bash_completion 가 regular file이 아니고
  #/etc/bash_completion가 regular file이라면 조건 만족
  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
  fi
fi

# ~/.bash_profile 이 regular 파일이라면 . ~/.bash_profile을 실행한다.
if [ -f ~/.bash_profile ]; then
    . ~/.bash_profile
fi
