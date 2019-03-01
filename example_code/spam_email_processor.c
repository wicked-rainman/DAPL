// Compile by linking with ../lib/libeml.a

#include "externs.h"
FILE *history;
void setup() {
        set_input(',',"../output/outfile.csv");
        set_graphics("fred2.dot","neato","svg");
        history=table("/home/susan/dev/tables/bad_ip.tbl");
}
void loop() {
        //if(match_substring("Received*.ip","46.161.42.") ) keep;
        if(match("Received*.ip","46.161.42.79") or match("Received*.ip","46.161.42.91")) keep;
        else drop;
        add_composite("Subject","X-Originating-IP Date,To");
        add_label("Subject","* Date");
        add_attributes("Subject","shape=none");
        lookup(history,"Received*.ip","*.history");
        add_label("Received*.ip","* *.asn *.country *.history");
        add_attributes("Received*.ip.history","color=red,shape=box");
        add_composite("Received*.ip","X-Originating-IP");
        if(match("Received*.ip.country","DE"))  add_attributes("Received*.ip","color=blue,shape=diamond");
        else add_attributes("Received*.ip","color=green,shape=diamond");
        add_attributes(last_value("Received*.ip"),"shape=house,color=red,style=bold");
        draw_chain("Subject","Received*.ip",'<');
}
