extern "C"
{
    #include "pxlib-0.6.3/include/paradox.h"
}

#include <iostream>
#include <vector>
#include <string>


std::string & xmlify_ampersand(std::string & str)
{
    int position = str.find( "&" );
    while ( position != std::string::npos )
    {
        str.replace( position, 1, "&amp;" );
        position = str.find( "&", position + 1 );
    } 
    return str;
}  










int main(int argc, char **  argv )
{
    if(argc<2)
    {
        std::cerr<<"usage: viral_paradox dbfile.db [blobfile.mb] \n";
        return 1;
    }
 


    std::cout<<"<paradox>\n";

    PX_boot();
 
    pxdoc_t *pxdoc; 
    pxdoc = PX_new();
    
    
    
    
    
    if(PX_open_file(pxdoc,argv[1]))
    {
        std::cerr<<"unable to open file"<< argv[1] <<"\n";
        return 1;    
    }

    
    
    if(argc>2)
    {
        PX_set_blob_file(pxdoc, argv[2]);
    }
    
    
    
    PX_set_parameter(pxdoc, "targetencoding","WINDOWS-1252");

    
    
    std::vector<std::string>  headers;
    
    for(int i=0;i<PX_get_num_fields(pxdoc);++i)
    {
        
        pxfield_t * f =PX_get_field(pxdoc, i);
        if(f==NULL)
        {
            std::cerr<<"unable to read field "<<i <<"\n";
            return 1;                
        }
        std::string fname(f->px_fname);
        xmlify_ampersand(fname);
        headers.push_back(fname);
    }
    
    
    
    
    for(int r=0;r<PX_get_num_records(pxdoc);++r)
    {
        
        pxval_t ** v= PX_retrieve_record(pxdoc, r);
        if(v==NULL)
        {
            std::cerr<<"unable to read record "<<r <<"\n";
            return 1;                
        }
        std::cout<<"\t<row>\n";            
        for(int i=0;i<PX_get_num_fields(pxdoc);++i)
        {
            std::cout<<"\t\t<"<<headers.at(i)<<">";
            
            
            pxval_t * pxf=v[i];
            
            
            switch(pxf->type) 
            {
                case pxfAlpha: 
                {
                    std::string lf(pxf->value.str.val,pxf->value.str.len);
                    xmlify_ampersand(lf);
                    std::cout<<lf;
                    break;
                }
                case pxfDate: 
                case pxfShort:
                case pxfAutoInc:
                case pxfLong:
                case pxfTimestamp:
                case pxfTime:
                case pxfLogical:                 
                {
                    std::cout<<pxf->value.lval;
                    break;
                }

                case pxfCurrency:
                case pxfNumber: 
                {
                    std::cout<<pxf->value.dval;
                    break;
                }
                
                case pxfBLOb:
                case pxfOLE:
                case pxfMemoBLOb:
                case pxfFmtMemoBLOb: 
                {
                    std::string lf(pxf->value.str.val,pxf->value.str.len);
                    xmlify_ampersand(lf);
                    std::cout<<"<![CDATA["<<lf<<" ]]>";
                    break;                        
                }            
                case pxfGraphic:    
                case pxfBCD: 
                default:
                    break;
            }
            
            
            std::cout<<"</"<<headers.at(i)<<">\n";      
                  
        }
        std::cout<<"\t</row>\n";                    
    }

    
    

    std::cout<<"</paradox>\n";
    
    
    PX_close(pxdoc);
    
    
    PX_delete(pxdoc);



    PX_shutdown();    
}


