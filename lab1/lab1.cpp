//Derek Boytim
//cse 660
//Lab1
//g++ -o lab1 lab1.cpp

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main() {
//STEP 1
    int FD_XYZ, FD_xx, charRead, charWritten, totalCharR=0, totalCharW=0;
    char buffer[200];
    
    FD_XYZ = creat("XYZ.doc", 384);
    
    //error handling
    if(FD_XYZ == -1) {cout <<"Error creating file XYZ.doc."; return -1;}
    
    FD_xx = open("/usr/class/cis660/xx.xx", O_RDONLY);

    //error handling
    if(FD_xx == -1) {cout <<"Error opening file xx.xx."; return -1;}
    
    charRead = read(FD_xx, &buffer, 200);
    while(charRead > 0) {
	charWritten = write(FD_XYZ, buffer, charRead);
	charWritten += write(FD_XYZ, "X1Y2A3", 6);
	totalCharR += charRead;
	totalCharW += charWritten;
	
	//error handling
	if(charWritten != charRead+6) {cout <<"Error writing to XYZ.doc."; return -1;}
	
	charRead = read(FD_xx, &buffer, 200);
    }
    
    //error handling
    if(charRead == -1) {cout <<"Error reading from xx.xx, interrupted."; return -1;}

    cout <<"STEP 1\n";
    cout <<"\tCharacters read from xx.xx: " <<totalCharR <<'\n';
    cout <<"\tCharacters written to XYZ.doc: " <<totalCharW <<'\n';

    close(FD_XYZ);
    close(FD_xx);
    
    
//STEP 2
    int FD_XXX, FD_WWW, totalCharXXX=0, totalCharWWW=0;

    FD_XYZ = open("XYZ.doc", O_RDONLY);
    FD_XXX = creat("XXX.txt", 384);
    FD_WWW = creat("WWW.txt", 384);

    charRead = read(FD_XYZ, &buffer, 40);
    while(charRead > 0) {
	int i, addedChars=0;
	for(i=0; i<charRead+addedChars; i++) {
	    if(buffer[i] == '1') {
		buffer[i] = ' ';
		int j;
		for(j=39+addedChars; j>i; j--) {
		    buffer[j+1] = buffer[j];
		}
		buffer[++i] = ' ';
		addedChars++;
	    }
	}
	charWritten = write(FD_XXX, buffer, charRead+addedChars);
	totalCharXXX += charWritten;

	charRead = read(FD_XYZ, &buffer, 20);
	if(charRead <= 0) {break;}
	for(i=0; i<charRead; i++) {
	    if(buffer[i] == '2') {
		buffer[i] = 'A';
	    }
	}
	charWritten = write(FD_WWW, buffer, charRead);
	totalCharWWW += charWritten;

	charRead = read(FD_XYZ, &buffer, 40);
    }

    cout <<"STEP 2\n";
    cout <<"\tCharacters written to XXX.txt: " <<totalCharXXX <<'\n';
    cout <<"\tCharacters written to WWW.txt: " <<totalCharWWW <<'\n';

    close(FD_XYZ);
    close(FD_XXX);
    close(FD_WWW);
    
    
//STEP 3
    FD_XXX = open("XXX.txt", O_RDWR);

    lseek(FD_XXX, 400, SEEK_SET);
    write(FD_XXX, "A1C2E3GHabcdefgh", 16);

    close(FD_XXX);
    
    
//STEP 4
    FD_WWW = open("WWW.txt", O_RDWR);

    lseek(FD_WWW, 0, SEEK_END);
    write(FD_WWW, "DerekBoytim", 11);

    cout <<"STEP 4\n";
    cout <<"\tCharacters written to WWW.txt: 11\n";

    close(FD_WWW);
    
    
//STEP 5
    int offset=-200, location;
    
    FD_WWW = open("WWW.txt", O_RDWR);

    location = lseek(FD_WWW, offset, SEEK_END);
    while(location>261) {
	read(FD_WWW, &buffer, 200);
	lseek(FD_WWW, location+16, SEEK_SET);
	write(FD_WWW, buffer, 200);
	offset -= 200;
	location = lseek(FD_WWW, offset, SEEK_END);
    }
    lseek(FD_WWW, 261, SEEK_SET);
    read(FD_WWW, &buffer, 200-(261-location) );
    write(FD_WWW, "ijklmnopI1K2M3OR", 16);
    write(FD_WWW, &buffer, 200-(261-location) );

    cout <<"STEP 5\n";
    cout <<"\tCharacters written to WWW.txt: 16\n";

    close(FD_WWW);
    
    
//STEP 6
    int FD_ZZZ;
    char buffer2[400];
    
    FD_ZZZ = creat("ZZZ.txt", 384);
    FD_XXX = open("XXX.txt", O_RDONLY);

    charRead = read(FD_XXX, &buffer2, 400);
    while(charRead > 0) {
	write(FD_ZZZ, buffer2, charRead);
	charRead = read(FD_XXX, &buffer2, 400);
    }

    close(FD_ZZZ);
    close(FD_XXX);
    
    
//STEP 7
    int totalCharZZZ=0;
    char buf;
    
    FD_ZZZ = open("ZZZ.txt", O_RDWR);
    FD_WWW = open("WWW.txt", O_RDONLY);

    lseek(FD_ZZZ, 0, SEEK_END);

    offset = -1;
    location = lseek(FD_WWW, offset, SEEK_END);
    while(location >= 0) {
	read(FD_WWW, &buf, 1);
	totalCharZZZ += write(FD_ZZZ, &buf, 1);
	location = lseek(FD_WWW, --offset, SEEK_END);
    }
    cout <<"STEP 7\n";
    cout <<"\tCharacters written to ZZZ.txt: " <<totalCharZZZ <<'\n';
    
    close(FD_ZZZ);
    close(FD_WWW);
    
    
//STEP 8
    int counter=0;
    char buffer3[80];
    
    FD_ZZZ = open("ZZZ.txt", O_RDONLY);
    charRead = read(FD_ZZZ, &buffer3, 80);
    counter++;
    cout <<"STEP 8\n";
    while(charRead > 0) {
	if(counter%100 == 0) {
	    int i;
	    cout <<'\t';
	    for(i=0; i<80; i++) {
		cout <<buffer[i];
	    }
	    cout <<'\n';
	}
	charRead = read(FD_ZZZ, &buffer3, 80);
	counter++;
    }

    close(FD_ZZZ);
    
    unlink("XYZ.doc");
    unlink("XXX.txt");
    unlink("WWW.txt");
    unlink("ZZZ.txt");
    
    return 0;
}
