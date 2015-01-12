#!/usr/bin/env ruby

File.open("temp.txt", "w") do |file|
  while gets
    file.write(Time.now.to_f.round(3).to_s + ' ' + $_)
  end
end