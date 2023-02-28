## Preamble
Inspired by darkscott, i decided to try a redis clone
few days ago I actually found a 
book \ blog on how to make one in c[^1]
the idea of this short project is to try 
not to follow the walkthrough 
but to try to remember what was said in it

It comes down to few "simple?" things
make a server that responds on http protocol
that runs on 80 port server,
although the port 80 is by convention and not required
and store key value pair in memory
The key can be used to hash the location 

## First Day: Write Hash Table in c
store information in memory using hashtable.
When it came down to hashing I thought about adding
the ascii of characters, but I decide to
instead that I'd searched for better hashing functions
I found FFNV-1a hash function[^2].
I thought it was really cool, specially because
it was a well written and easy to understand pseudo code

I wrote some part of it
I was able to store strings key value pair
I was able to look up the key
so there's that
the server part will be more challenging.

## End of First Day 
While I'm with family, I'm looking
for resources. im searching the www looking for info
well I think I understand the how to make a simple
http server it's a server - client relationship
See HTTP made easy[^3].

## Second Day
I remember we wrote a simple server using sockets
if i can find that then maybe i can use some of that

Yeah so looking at how to use sockets again. 
It requires quite a bit of boilerplate code
to use. I did learn that it is
very much server client 

Towards the end of my coding sessions I was
able to get it working. 
I was able to respond to a web browser request.
It was so interesting to have have it working, even
if it's partially. The HTTP makes so much sense now.
It's just sending text around.
The very first line is VERB Resource version

The next step was going to be to tie it all 
together. The idea was to parse the
request into adding or getting to from 
the hash table. 

The only after thought is scalability.
For that, I would just make it so
every client owns a resource.
In such case every client would
get their own hash table.
Of course this could only scale so much
before running out of memory.

## Final thought
This was so much fun. Although,
it is pretty unsecure. It uses very simple
HTTP server knowledge. Also, 
it uses a very simple buffer that should
should be easily exploitable.

## Final final thought
After all that, I realize that 
I'm not storing the key in my hash table.
So, while the key allows me to hash
and get the value from the hash table,
I'm unable to verify the actual key.
Therefore, if two keys hash to the same
location, they will be stored,
but only one value will be retrieve.
Well due to my lazyness, it seems that
a key that hashes to a taken space will
overwrite the previous value
so that's 2 problems to fix

other[^4] useful[^5] links[^6]

reference links:
[^1]: https://build-your-own.org/redis/01_intro_redis
[^2]: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
[^3]: https://www.jmarshall.com/easy/http/
[^4]: https://benhoyt.com/writings/hash-table-in-c/
[^5]: https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
[^6]: https://stackoverflow.com/questions/176409/build-a-simple-http-server-in-c
