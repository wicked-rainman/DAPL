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
      Code within the loop block is generally fault tollerant. For example, function references to 
      field names that are non-existant result in the calling function failing gracefully. This 
      allows for the successful processing of input files that have different fieldnames where not
      all fields are present in each file. 
      
2. Setup functions.
      Setup functions populate a range of global variables that are made available to functions
      within the loop block. For example, the setup function "set_input" populates a file pointer
      that is read to provide input data. "set_input_directory" populates an array of input filenames
      that results in iterative calls to "set_input". Current setup functions are:
      
            define_input_fieldnames -----------------------------------
            
            When an input file does not have a field descriptor tag line, define the 
            input fieldnames in a file, and how they are deliminate.
 
            define_csv_tag("tag_string") ------------------------------
 
            Define the start string that indicates a field descriptor line in an
            input file.
 
            set_input_directory ---------------------------------------
            
            Specify a directory name where the input files reside. All files in
            this directory will be processed. 
 
            set_input -------------------------------------------------
            
            Defines the field delimiter, and a list of one or more input files
            
            set_output ------------------------------------------------
            
            Defines the output file for any saved records
            
            set_graphics ----------------------------------------------
            
            Defines the output file for any generated .dot graphics.
            
            table -----------------------------------------------------
            
            Defines a file that contains records that are used as a  lookup table
      

3. Loop functions

      

      
    

