# http-server
## A multi-threaded HTTP/1.1 server, written in C 99 for educational purpose.

## /!\ Warning : 

DO NOT USE THAT IN ANY ENVIRONMENT THAT IS NOT DEDICATED TO ***BASIC TESTS***. IT IS NOT SAFE AND NEITHER EFFICIENT. If anything breaks because you used this server in a production environement, I shall not be held responsible for the damage it caused.

Enjoy!

### __What does it do__ ?

- It runs a very basic HTTP/1.1 server on your own machine, and allows you to make get requests through it to render HTML webpages, CSS pure text, images (both jpg and png).

### __Requirements__

- C compiler (gcc or clang worked juste fine for me), and the standard lib that goes with it. Nothing else really.


### __How to install it on your computer ?__

- Just clone it wherever you want in your computer, using : 
```ps
git clone https://github.com/Esteban795/http-server.git
```

- When inside the correct folder, you can run 
```ps
make all
``` 
to both build and run the server on port 8080. If you want to run it on a specific port, you should do 
```ps
make build
./bin/server <port>
```
because arguments with makefiles are a pain to deal with.

- It should print
```txt
Server all set up and listening on port <8080 or your own port>
```

## __How to use it ?__

- Open your web browser, go to localhost:\<yourport\> and thne you can change the url to 
```txt
localhost:<yourport>/index.html
```
for example, and it should render the html template (linked with style.css) just fine.
Please keep in mind that ***anything*** within the `static` folder can be accessed through the server using the UNIX path system (for example, `/test/tests/ok.jpg` would render the file in `http-server/static/test/tests/ok.jpg` if it exists), but objects *outside* the static folder won't be find by the program.



## __Known issues__ 

- Images not fully rendering : it is because the OS decides to cut CPU time for the program and it doesn't continue. I need to write a function to make sure that every byte is sent.