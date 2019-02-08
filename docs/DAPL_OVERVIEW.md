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
      
            Defines the separator that is present in the input record to delimit each field ('dlm')
            Defines the name for each field present in the input records ("Fieldname1......Etc")
            
