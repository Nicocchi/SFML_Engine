#!/bin/bash

# Parse arguments
POSITIONAL=()
VIRTUAL="false"

while [[ $# -gt 0 ]]; do
	key="$1"

	case $key in
	-n | --name)
		NAME="$2"
		shift # past argument
		shift # past value
		;;
	-f | --filepath)
		FILEPATH="$2"
		shift # past argument
		shift # past value
		;;
	-nf | -fn)
		NAME="$2"
		FILEPATH="$2"
		shift # past argument
		shift # past value
		;;
	-e | --extension)
		EXTENSION="$2"
		shift # past argument
		shift # past value
		;;
	-v | --virtual)
		VIRTUAL="true"
		shift # past argument
		shift # past value
		;;
	-b | --base)
		BASE="$2"
		shift # past argument
		shift # past value
		;;
	-a | --access)
		ACCESS="true"
		shift # past argument
		shift # past value
		;;
	-nv | -vn)
		NAME="$2"
		VIRTUAL="true"
		shift # past argument
		shift # past value
		;;
	-nfv | -nvf | -fnv | -fvn | -vnf | -vfn)
		NAME="$2"
		FILEPATH="$2"
		VIRTUAL="true"
		shift # past argument
		shift # past value
		;;
	-h | --help)
		echo ""
		echo "C++ Class Creation Toolkit"
		echo ""
		echo "-n --name		File Name (without extension)"
		echo "-f --filepath		File Path within src & include"
		echo "-e --extension		Header file extension"
		echo "-v --virtual		Virtual class"
		echo "-b --base		Base class"
		echo "-a --access		Public or Private class access"
		echo "-h --help		Show help menu"
		echo ""
		echo "You can combine commands. Combining -nf will give the same file path as the name."
		exit 1
		shift # past argument
		shift # past value
		;;
	--default)
		DEFAULT=YES
		shift # past argument
		;;
	*)                  # unknown option
		POSITIONAL+=("$1") # save it in an array for later
		shift              # past argument
		;;
	esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

if [ -z "$NAME" ]; then
	echo "Need to specify a name"
	echo ""
	echo "C++ Class Creation Toolkit"
	echo ""
	echo "-n --name		File Name (without extension)"
	echo "-f --filepath		File Path within src & include"
	echo "-e --extension		Header file extension"
	echo "-v --virtual		Virtual class"
	echo "-b --base		Base class"
	echo "-a --access		Public or Private class access"
	echo "-h --help		Show help menu"
	echo ""
	echo "You can combine commands. Combining -nf will give the same file path as the name."
	exit 1
fi

if [[ $NAME == *[_]* ]]; then
	NAME_NO_UNDERSCORE="${NAME//_/}"
else
	NAME_NO_UNDERSCORE="${NAME//_/}"
fi

# NAME_UNDERSCORE="${NAME// /_}"

if [ -z "$EXTENSION" ]; then
	EXTENSION="hpp"
fi

if [ "${VIRTUAL}" == "true" ]; then
	MEMBER="virtual ~$NAME_NO_UNDERSCORE();"
else
	MEMBER="~$NAME_NO_UNDERSCORE();"
fi

if [ "${ACCESS}" == "true" ]; then
	CLASS_ACCESS="public"
else
	CLASS_ACCESS="private"
fi

uuid=$(uuidgen)
uuid=${uuid//-/}
uuid=${uuid^^}
uuid=${uuid:1:12}

# Create directory and file if not exists
mkfileP() {
	mkdir -p "$(dirname "$1")" || return
	touch "$1"
}

# Get CWD
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
# Dirs
export src=src
export include=include

# Header File
if [ -z "$BASE" ]; then
	HPP_CONTENT="#ifndef __${NAME^^}_${EXTENSION^^}_${uuid}_
#define __${NAME^^}_${EXTENSION^^}_${uuid}_

class ${NAME_NO_UNDERSCORE}
{
private:
    // Members

public:
    ${NAME_NO_UNDERSCORE}();
    ${MEMBER}
};

#endif // __${NAME^^}_${EXTENSION^^}_${uuid}_"
else
	HPP_CONTENT="#ifndef __${NAME^^}_${EXTENSION^^}_${uuid}_
#define __${NAME^^}_${EXTENSION^^}_${uuid}_

#include \"${BASE}.${EXTENSION}\"

class ${NAME_NO_UNDERSCORE} : ${CLASS_ACCESS} ${BASE}
{
private:
    // Members

public:
    ${NAME_NO_UNDERSCORE}();
    ${MEMBER}
};

#endif // __${NAME^^}_${EXTENSION^^}_${uuid}_"
fi

# Source File
CPP_CONTENT="#include \"${NAME_NO_UNDERSCORE}.${EXTENSION}\"

${NAME_NO_UNDERSCORE}::${NAME_NO_UNDERSCORE}()
{

}

${NAME_NO_UNDERSCORE}::~${NAME_NO_UNDERSCORE}()
{

}
"

# Create the files
if [ -z "$FILEPATH" ]; then
	mkfileP ${DIR}/${include}/$NAME_NO_UNDERSCORE.$EXTENSION && echo "$HPP_CONTENT" >${DIR}/${include}/$NAME_NO_UNDERSCORE.$EXTENSION && echo "$NAME_NO_UNDERSCORE.$EXTENSION created in $DIR/include" || echo "Failed to create $DIR/include/$NAME_NO_UNDERSCORE.$EXTENSION"
	mkfileP ${DIR}/${src}/$NAME_NO_UNDERSCORE.cpp && echo "$CPP_CONTENT" >${DIR}/${src}/$NAME_NO_UNDERSCORE.cpp && echo "$NAME_NO_UNDERSCORE.cpp created in $DIR/src" || echo "Failed to create $DIR/src/$NAME_NO_UNDERSCORE.cpp"
else
	mkfileP ${DIR}/${include}/$FILEPATH/$NAME_NO_UNDERSCORE.$EXTENSION && echo "$HPP_CONTENT" >${DIR}/${include}/$FILEPATH/$NAME_NO_UNDERSCORE.$EXTENSION && echo "$NAME_NO_UNDERSCORE.$EXTENSION created in $DIR/include/$FILEPATH" || echo "Failed to create $DIR/include//$FILEPATH/$NAME_NO_UNDERSCORE.$EXTENSION"
	mkfileP ${DIR}/${src}/$FILEPATH/$NAME_NO_UNDERSCORE.cpp && echo "$CPP_CONTENT" >${DIR}/${src}/$FILEPATH/$NAME_NO_UNDERSCORE.cpp && echo "$NAME_NO_UNDERSCORE.cpp created in $DIR/src/$FILEPATH" || echo "Failed to create $DIR/src//$FILEPATH/$NAME_NO_UNDERSCORE.cpp"
fi
