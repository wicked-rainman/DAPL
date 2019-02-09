DAPL is intended to simplify the process of analysing large volumes of single-line records (HTTP, 
SSH, Audit logs Etc). Provisions are made for dealing with other data forms through a conversion 
process known as imput handling (Currently only E-mail). A small range of standalone utilities that 
aid dealing with IP related data have been included, albeit they are separate (but replicated) from 
the core DAPL system.

1. The core DAPL wrapper.

      Provision is made for two code blocks within any main routine - setup() and loop(). 
  
      setup():
    
      Code within the setup block is executed once after program initialisation. It's purpose 
      is to allow the user to perform startup functions like opening input and output files, 
      defining input fields, identifying reference files Etc. Any failures within the setup 
      block stops the whole process running.
      
      loop()
  
      Code within the loop block is executed once for each record contained in each input file
      identified in setup(). A data structure is created for each record, populated with each 
      fieldname and field value found. All functions within the loop block reference this global
      structure. Once the record has been processed, the structure is removed, ready to be populated 
      with the fields in the next record. Other than maintaining a count of input and output records
      and maintaining file or memory pointers for any reference files, there is no state within the
      code block. This allows for processing of undefinably large volumes of input.
      
2. Setup functions.

      define_input_fieldnames('dlm',"Fieldname1, Fieldname2, FieldnameN")
      
            First parameter Defines the field separator present in each input record
            Second parameter Defines the name for each field in the input records.
 
      define_csv_tag("tag_string")
      
            Where input files have a tag line that defines fields within each record
            fieldnames will not need defining. The single parameter to this function
            indicates the start string that defines a tag line (eg, "#Fields:")
            
      set_input_directory('dlm',"directory name")

            First parameter defines the field separater present in each input record
            Second parameter defines the input directory name (including trailing '/')

      set_input('dlm',"input filename(s)")

            First parameter defines the field separater present in each input record
            Second parameter defines one or more input filenames.

      set_output("outfile_name")
      
            Defines the full path name for any record output file.

      set_graphics("outfile_name","render_engine")
      
            First parameter defines a full path to the graphics output filename
            Second parameter defines the graphics render engine that will be used

      table("table_name")
      
            Parameter is the full path filename for a memory-stored lookup table.
            Result from the call is stored in a global FILE variable.

3. Loop functions

      add_asn("fieldname")
      
            Parameter is the name of a field that should contain a dotted decimal notation IP address
            IP address is looked up in file $ASN_FILE, and the ASN added as "fieldname.asn"
            This is a local lookup and depends on an up to date ASN_FILE.
      
      add_attributes("fieldname","attributes")
      
            A graphics function. First parameter is the fieldname that attributes will be added for.
            Second parameter is a string containing the (.dot compatible) attributes to be used.
      
      add_composite("fieldname","composite_fieldname(s)")
      
            A graphics function. First parameter is the fieldname that composites will be added to.
            Second parameter is a list of one or more fieldnames whoes value will be used to create 
            the composite. When using graphics, adding composite values makes a node unique. 
      
      add_concatenation("new fieldname","fieldname(s)")
      
            Creates a new fieldname that contains the field values specified by one or more existing
            fieldname(s). 
      
      add_country("fieldname")
      
            Parameter is the name of a field that should contain a dotted decimal notated IP address
            IP address is looked up in file $COUNTRY_FILE, and the country diagraph added as 
            "fieldname.country". This is a local lookup and depends on an up to date COUNTRY_FILE.
      
      add_field
      
      add_label
      
      add_reverse_dns
      
      add_substring
      
      draw_attached
      
      draw_chain
      
      draw_node
      
      draw_path
      
      drop_rec
      
      insert_new_field
      
      keep_rec
      
      last_fieldname
      
      last_value
      
      lookup
      
      match
      
      pattern
      
      remove_chars
      
      remove_string
      
      rename_field
      
      replace_char
      
      socketadd_asn
      
      socketadd_country
      
      substring
      
      unescape
      
      unix_time
      
      urldecode
      
      write_csv_fields
