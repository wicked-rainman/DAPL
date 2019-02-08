DAPL is intended to simplify the process of analysing large volumes of single-line records (HTTP, 
SSH, Audit logs Etc). Provisions are made for dealing with other data forms through a conversion 
process known as imput handling. A small range of standalone utilities that aid dealing with IP 
related data have been included, albeit they are separate (but replicated) from the core DAPL system.

1. The wrapper.

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
      structure. Once the record has been processed, the structure is removed.
      
2. Setup functions.

      define_input_fieldnames('dlm',"Fieldname1, Fieldname2, FieldnameN")
      
            First parameter Defines the field separator present in each input record
            Second parameter Defines the name for each field in the input records.
            
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
            
