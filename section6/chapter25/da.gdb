#fileName : da.gdb
#define a function to dump pointers array

define da

  if $argc != 2
    help da
  else

    set $pointer  = $arg0
    set $number  = $arg1

    printf "Dump %d items begin with %p\n",$number, $pointer
    set $count = 0
    set $n = $number
    while $n--
        p * $pointer[$count++]@$number
    end

  end

end

document da
  usage: da pointer number
end
