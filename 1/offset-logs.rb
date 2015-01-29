#!/usr/bin/env ruby

File.open('offsetted.txt','w'){ |f|
  IO.readlines('logfile.txt').each{ |l|
    s = l.split
    s[0] = s[0].to_f - 1421061133.079
    s[0] = s[0].round(3)
    f.write(s[0].to_s + ' ' + s[1] + "\n")
  }
}