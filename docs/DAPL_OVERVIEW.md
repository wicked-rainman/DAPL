DAPL is intended to simplify the process of analysing large volumes of single-line records (HTTP, 
SSH, Audit logs Etc). Provisions are made for dealing with other data forms through a conversion 
process known as imput handling. A small range of standalone utilities that aid dealing with IP 
related data have been included, albeit they are separate (but replicated) from the core DAPL system.

1. The wrapper.

  A. Provision is made for two code blocks within any main routine - setup() and loop(). 
  
    setup():
    
      Code within the setup block is executed once after program initialisation. It's purpose 
      is to allow the user to perform startup functions like opening input and output files, 
      defining fields, identifying reference files Etc. Any failures within the setup block 
      stop the whole process running.
      
    loop()
  
      Code within the loop block is executed for each record contained in each input file
      identified in setup()
