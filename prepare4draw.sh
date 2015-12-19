#/bin/bash

INPUT=$1
SCALE=01
EXP=$2
DIR=$(pwd)

# general x 
cat $INPUT/output/pdfs_q2val_$SCALE.txt | awk '{print $1}' | tail -n +3 > store/central-x 

# central gluon, up, down
cat $INPUT/output/pdfs_q2val_$SCALE.txt | awk '{print $2}' | tail -n +3 > store/gluon_01-central-$EXP
cat $INPUT/output/pdfs_q2val_$SCALE.txt | awk '{print $7}' | tail -n +3 > store/up_01-central-$EXP
cat $INPUT/output/pdfs_q2val_$SCALE.txt | awk '{print $8}' | tail -n +3 > store/down_01-central-$EXP

#experimental uncert
# put into nice format. 
# for each source --> x central up down
for i in {01..18}; do
    #Gluon
    cat $INPUT/output/pdfs_q2val_s"$i"p_01.txt | awk '{print $2}' | tail -n +3 > store/gluon_expP"$i"   
    cat $INPUT/output/pdfs_q2val_s"$i"m_01.txt | awk '{print $2}' | tail -n +3 > store/gluon_expM"$i" 
    paste -d " " store/central-x store/gluon_01-central-$EXP store/gluon_expP"$i" store/gluon_expM"$i" > store/gluon_expS"$i"-$EXP
    #Up quark
    cat $INPUT/output/pdfs_q2val_s"$i"p_01.txt | awk '{print $7}' | tail -n +3 > store/up_expP"$i"   
    cat $INPUT/output/pdfs_q2val_s"$i"m_01.txt | awk '{print $7}' | tail -n +3 > store/up_expM"$i" 
    paste -d " " store/central-x store/up_01-central-$EXP store/up_expP"$i" store/up_expM"$i" > store/up_expS"$i"-$EXP
    #Down quark
    cat $INPUT/output/pdfs_q2val_s"$i"p_01.txt | awk '{print $8}' | tail -n +3 > store/down_expP"$i"   
    cat $INPUT/output/pdfs_q2val_s"$i"m_01.txt | awk '{print $8}' | tail -n +3 > store/down_expM"$i" 
    paste -d " " store/central-x store/down_01-central-$EXP store/down_expP"$i" store/down_expM"$i" > store/down_expS"$i"-$EXP
    
    rm store/gluon_expP"$i"
    rm store/gluon_expM"$i"
    rm store/up_expP"$i"
    rm store/up_expM"$i"
    rm store/down_expP"$i"
    rm store/down_expM"$i"
  
done

#list of sources
if [ $EXP == "hera" ]; then
    ls -ltrh $DIR/store | grep hera | grep expS | grep gluon | grep -v hera+cms | awk '{print $9}' > store/list-sources-gluon-$EXP
    ls -ltrh $DIR/store | grep hera | grep expS | grep up | grep -v hera+cms | awk '{print $9}' > store/list-sources-up-$EXP
    ls -ltrh $DIR/store | grep hera | grep expS | grep down | grep -v hera+cms | awk '{print $9}' > store/list-sources-down-$EXP
else
    ls -ltrh $DIR/store | grep $EXP | grep expS | grep gluon | awk '{print $9}' > store/list-sources-gluon-$EXP
    ls -ltrh $DIR/store | grep $EXP | grep expS | grep up | awk '{print $9}' > store/list-sources-up-$EXP
    ls -ltrh $DIR/store | grep $EXP | grep expS | grep down | awk '{print $9}' > store/list-sources-down-$EXP
fi



