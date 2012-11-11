
#
# Quotes regular expression metacharacters. Outputs the transformed string.
#
# \param line the line to quote.
#
function quote_meta {
    echo $1 | sed 's/\\/\\\\/g; s/\//\\\//g'
}

#
# Determines whether or not a file contains a block of text.
# Issues no output
#
# \param file the name of the file to check
# \param block the anme of a file containing the block of text to search for.
#
# \return 0 if the block was found, 1 otherwise.
#
function contains-block {
    local file=$1;
    local blockf=$2;
    shift 2

    local block_start=`head -n 1 $blockf`
    local block_end=`tail -n 1 $blockf`

    local t=$(tempfile)

    sed -n "\@$block_start@,\@$block_end@ p" $file > $t
    diff -q $t $blockf > /dev/null 2>&1
    local status=$?
    
    rm -f -- $t

    return $status
}

#
# Prepends the contents of one file to another, encapsulated by pre and post.
#
# \param file the name of the file to modify.
# \param pre the pre text to insert immediately before the text block.
# \param block the name of the file containing the block to prepend.
# \param post the post text to insert immediately following the text block.
#
function prepend-block {
    local file=$1
    local pre=$2
    local blockf=$3
    local post=$4
    shift 4

    contains-block $file $blockf
    if [ $? -ne 0 ]; then
        local t=$(tempfile)
       
        # build the new file
        echo "$pre" > $t
        cat $blockf >> $t
        echo "$post" >> $t
        cat $file >> $t

        # swap with original
        mv -f $t $file
    fi

}

