# usage: ./generate-data.sh <number-of-seconds>

if [ -z "$*" ]; then
	echo "usage: ./generate-data.sh <number-of-seconds>"
	exit 1
fi

vmstat 1 $1 | ./add-timestamps.rb
tail -n+3 temp.txt | awk '{print $1, $14+$15}' > logfile.txt
rm temp.txt
# notify-send "Finished generating CPU usage data"
./offset-logs.rb
gnuplot plot-points.txt
gnuplot plot-histog.txt
pandoc report.md -o report.pdf