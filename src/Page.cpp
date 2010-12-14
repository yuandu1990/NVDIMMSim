//Page.cpp
//.cpp file for the page class

#include "Page.h"

using namespace std;
using namespace NVDSim;

Page::Page(){

}

Page::Page(uint page){
	page_num = page;
}

void *Page::read(uint size, uint word_num){
        
        uint word = word_num;
        
        // this variable will hold the data we agrigate from the pages
	void *data;

	uint temp_size = size;

	// sanity check
	if (size > PAGE_SIZE){
	  	DEBUG("Request to read page "<<word<<" failed: requested to read more data than page could hold");
		return (void *)0x0;
	}

	// we're reading multiple pages worth of data
	while(temp_size > WORD_SIZE){
	  if (word_data.find(word) == word_data.end()){
		DEBUG("Request to read page "<<word<<" failed: nothing has been written to that address");
		return (void *)0x0;
	  }
	  // data doesn't actually matter, its just a placeholder
	  // so we're just going to overwrite the pointer and pretend that we're making a packet out of pages
	  data = word_data[word];

	  // we've got one words worth of the stuff we were supposed to get
	  temp_size =  temp_size - WORD_SIZE;

	  // we're done with this word, move to the next word
	  word = word + 1;	  
	}

	if (word_data.find(word) == word_data.end()){
		DEBUG("Request to read page "<<word<<" failed: nothing has been written to that address");
		return (void *)0x0;
	}
	data = word_data[word];

	return data;
	
}

void *Page::read(){
  return (void *)0x0;
}

void Page::write(uint size, uint word_num, void *data){
 
        uint word = word_num;
        uint temp_size = size;
	
	// writing data across multiple pages
	while(temp_size > WORD_SIZE){
       
	  // if this word has not yet been accessed yet, create a new word object for it and add it to the words map
	  if (word_data.find(word) == word_data.end()){
		word_data[word]= data;
	  } else{
	    /*ERROR("Request to write page "<<page_num<<" failed: page has been written to and not erased"); 
	      exit(1);*/
		
	    //Until garbage collection is implemented, you can write to pages that have already been written to
	    word_data[word] = data;
	  }
	  
	  // we've written one pages worth of the stuff we were supposed to write
	  temp_size = temp_size - WORD_SIZE;

	  // we're done writing to this page, move on to the next page
	  word = word + 1;
	}


	if (word_data.find(word) == word_data.end()){
		word_data[word]= data;
	} else{
		/*ERROR("Request to write page "<<word_num<<" failed: word has been written to and not erased"); 
		exit(1);*/
		
		//Until wear leveling is implemented, you can write to words that have already been written to
		word_data[word] = data;
	}
}

void Page::write(){
  // doesn't do anything
}
