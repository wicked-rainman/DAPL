Storing the replies to historic DNS requests seems a huge resource-expensive task. For what purpose ?

- In web-hosting environments, a single machine with 1 IP address may deliver the content for many web sites.
Storing historical DNS replies allows you to find out what websites (or other entities with a DNS entry) are 
being hosted on that single machine.
- If someone hosts a website from home on a dynamic IP address, storing historic DNS associates the dynamically
allocated IP addresses (and therefore the rdns entry) with the website name. 
- Having a store of DNS replies enables threaded regular expression pattern matching agains domain names. This 
is useful for understanding what assets are associated with a company or organisation.
