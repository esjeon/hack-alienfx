#!/bin/sh

if [ $# -ne 1 ]; then
	echo "Usage: $0 <iface>"
	echo "       $0 -"
	echo
	echo "       Enter 'q' or EOF to stop capturing"
	exit
fi

if [ "$1" = "-" ]; then
	tshark -D
	exit
fi

capfile="dump-$$.pcapng"
seqfile="seq-$$.txt"
filter="usb.setup.bRequest == 9"
iface="$1"

if [ -f "${capfile}" -o -f "${seqfile}" ]; then
	echo "Output files already exist. Exiting to prevent over-writing"
	exit 0
fi

echo "PID = $$"

tshark -i "${iface}" -F pcapng -l -w "${capfile}" &
cpid=$!
while read line; do
	if [ "${line}" = 'q' ]; then
		break
	fi
done

kill -TERM "${cpid}"
wait

echo "Extracting data..."
tshark -r "${capfile}" -Y "${filter}" -T fields -e usb.capdata > "${seqfile}" 

