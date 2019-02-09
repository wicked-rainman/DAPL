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
      
      define_input_fieldnames
            
            When an input file does not have a field descriptor tag line, define the 
            input fieldnames in a file, and how they are deliminate.
            
      define_csv_tag
 
            Define the start string that indicates a field descriptor line in an
            input file.
 
      set_input_directory 
            
            Specify a directory name where the input files reside. All files in
            this directory will be processed. 
 
      set_input 
            
            Defines the field delimiter, and a list of one or more input files
            
      set_output 
            
            Defines the output file for any saved records
            
      set_graphics 
            
            Defines the output file for any generated .dot graphics.
            
      table 
            
            Defines a file that contains records that are used as a  lookup table
      
      Examples demonstrating the use of these setup functions can be found in the ./example_code directory
      
3. Loop functions

      Loop functions tend to fall into one of three categories:
      
            1. Those that Enable the selection or rejection of individual records, based on
            string matching, substring matching or through regular expression pattern matching. 
            Rejected records are internally assigned a "drop" flag. If a drop flag is 
            present, all sequentially following loop functions will exit without performing their 
            intended actions (I.E, the record is ignored). Early rejection of unwanted records 
            can obviously dramatically improve processing times.
            
            2. Value editing functions that can replace, sanitse, substring or add to the underlying
            data in some way. Field values can be looked up in locally held tables, or from external
            sources via socket calls with suitable APIs. Field values can be combined or added to in order
            to make them unique (such as adding DTGs Etc). 
            
            3. Graphical data modeling. Relationships between data fields can be defined and visualised
            by generating .dot output that can be rendered in various ways (such as SVG, PDF JPEG Etc).
            Duplicate relationships are set to be effectively de-duped by the .dot processor, making
            large volumes of data easier to analyse. 
      
      Most loop functions have the same startup logic:
      
            1. Check to see if the drop flag has been set. If it has, return.
            2. Make a call to "find_fieldname" to see if the target field is present. If it's not, return.
  
      The function then performs whatever logic is intended, which invariably ends up with a new 
      fielname/fieldvalue pair being inserted into the global data structure via a call to 
      "insert_new_field". If a modified field value (rather than new field) is to be replaced, all functions 
      check that the new field value does not exceed MAX_FIELDVALUE_LENGTH and that MAX_FIELD_COUNT is not
      exceeded. Both these values have been arbitrarily set. 
      
      Most loop functions are small and source code can be found in the ./src directory. Using these as a
      template should make adding any new functionality simple, but making such additions are not considered
      to be a DAPL users job!
      
