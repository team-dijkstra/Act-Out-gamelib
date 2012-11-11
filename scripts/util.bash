
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

    local block_start=$(quote_meta "`head -n 1 $blockf`")
    local block_end=$(quote_meta "`tail -n 1 $blockf`")

    local t=$(tempfile)

    sed -n "/$block_start/,/$block_end/p" $file > $t
    diff -q $t $blockf > /dev/null 2>&1
    local status=$?
    
    rm -f -- $t

    return $status
}

