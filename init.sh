FOLDER=containers_test
URL=https://github.com/mli42/containers_test.git

if [ ! -d "$FOLDER" ] ; then
	git clone "$URL" "$FOLDER"
fi