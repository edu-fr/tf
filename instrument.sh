#!/bin/bash

# this is left as an example 
function compile() {

  if [[ -n $CPU2006 && $CPU2006 -eq 1 ]]; then
    # Convert the program to SSA form:
    $LLVM_PATH/opt -mem2reg -load DCCBasilisk.$suffix -Instrument -S $btc_name -o $rbc_name ;
    # Compile our file, in IR format, to x86:
    $LLVM_PATH/llc -filetype=obj $prf_name -o $obj_name ;
    # Compile everything now, producing a final executable file:
    $LLVM_PATH/$COMPILER -lm $BASILISK_PATH/Collect/collect.o $obj_name -o INS_$exe_name ;
    
    return
  fi

  # source_files is the variable with all the files we're gonna compile

  for file_name in "${source_files[@]}"; do
    base_name=$(basename $file_name .c) ;
    btc_name="$base_name.bc" ;
    rbc_name="$base_name.rbc" ;
    # Convert the target program to LLVM IR:
    $LLVM_PATH/$COMPILER $CXXFLAGS -g -c -emit-llvm $file_name -o $btc_name ;
    # Convert the target IR program to SSA form:
    # $LLVM_PATH/opt $btc_name -o $rbc_name ;

    # You can add llvm pass in the command above:
    $LLVM_PATH/opt -mem2reg -load DCCBasilisk.$suffix -Instrument -S $btc_name -o $rbc_name ;
  done

  #Generate all the bcs into a big bc:
  $LLVM_PATH/llvm-link *.rbc -o $lnk_name ;

  # Insert instrumentation in the program:
  $LLVM_PATH/opt $lnk_name -S -o $prf_name ;
    
  # Compile our instrumented file, in IR format, to x86:
  $LLVM_PATH/llc -filetype=obj $prf_name -o $obj_name ;
  # Compile everything now, producing a final executable file:
  $LLVM_PATH/$COMPILER -lm $BASILISK_PATH/Collect/collect.o $obj_name -o INS_$exe_name ;
}