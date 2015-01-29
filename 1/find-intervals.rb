#!/usr/bin/env ruby

File.open('intervals.txt','w'){ |f|
  timestamps, values = IO.readlines('offsetted.txt').map(&:split).transpose
  intervals = timestamps.each_cons(2).map { |t1, t2| (t2.to_f - t1.to_f).round(3).to_s }
  # intervals.zip(values).each { |i, v| f.write(i + ' ' + v + "\n") }
  intervals.each { |i| f.write(i + "\n") }
}