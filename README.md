# CoogleEngine
Meet Coogle: a search engine for text files written in C.

## The Goal 
Say we have a large directory of text files. We need to identify files of interest that contain certain words or phrases. Looking through each file would be incredibly time consuming. How could we programatically rank files by their relevance to a certain search phrase? 

The solution is split into three phases:
1. **Training Phase**
2. **Search Phase**
3. **Destroy Phase**

To rank documents by their relevance to a search query we will first organize the text data contained in all files into an efficently searchable structure (Training Phase). Next, we will search the organized text data using a popular ranking algorithm (Search Phase). Finally, to prevent memory leaks all allocated memory will be freed before the user exits the program (Destroy Phase).

#### Training Phase
1. Read in a directory containing text files from the user.
2. Create a custom hashmap structure which will store all text data in a more searchable form. 
3. Add each word to the hashmap along with the doucments the word appears in (and the frequency in each document).
4. Remove words that appear in all documents to improve search efficiency

#### Search Phase 
1. Read in a search query from user.
2. For each document in the directory calculate a ranking score based on the words in the query.
3. Save rankings to a file and display rankings to the user.

#### Destroy Phase
1. Iterate through each hashmap linked list to free all memory allocated for linked list nodes.
2. Free memory allocated for the hashmap struct itself.
3. Exit program.

Now let's take a look at the ranking algorithm we'll use to determine which documents are most relevant:

## Term Frequency-Inverse Document Frequency (TF-IDF) page rank algorithm

The term frequency-inverse document frequency (tf-idf) method is one of the most common weighting algorithms used in many information retrieval systems as well as in many Natural language processing (NLP) systems. 

A search query submitted by a user of the search engine typically consists of a number of words/terms. Therefore, we have to determine the relevance, or rank, of the document for the entire search phrase consisting of some m number of words w1, w2....wm , using the tf-idf scores for each word. The relevance, or rank, Ri of document i for this search phrase consisting of m words, is defined as the sum of the tf-idf scores for each of the m words.

The tf-idf score gives us a measure of how important a word is to a document among a set of documents. It uses local term frequency (occurences of a word within a single document) and global inverse document frequency (inverse of occurences of the word across documents) to scale down the score of common terms and scale up the score of rare terms.

The tf-idf(w,i) weight of a term (word) w in document i is the product of its term frequency tf(w,i) and inverse document frequency idf(w).
```
tf-idf(w,i) = tf(w,i) × idf(w)

The tf-idf(i) rank of a document i is the sum of the tf-idf scores for each of the m words in the search query.

tf-idf(i) = tf-idf(w1,i) + tf-idf(w2,i) + tf-idf(w3,i) + ... + tf-idf(wm,i)
```

#### Term Frequency (tf): 
The term frequency tf(w,i) of a term (word) w in document i is the raw frequency of the word in the document. There are variations of term frequency that are used in different search algorithms; for example, since raw frequency may not always relate to relevance they divide the frequency by the number of words in the document to get a normalized raw frequency.

#### Inverse Document Frequency (idf): 
Many times a rare term/word is more informative than frequent terms. Stop words (such as “the” “for” etc.) appear often and usually are not very informative as to the relevance of a document. The inverse document frequency idf(w) considers how frequent the word occurs across the documents being searched. It is the natural log of the number of documents in the direcory being searched (N) divided by the document frequency df(w) which is the number of documents that contain the word w.
```
idf(w) = log (N / df(w))
```
If no documents contain the word then df(w)=0 so 1 must be added to the denominator of the above equation to handle the divide by zero case. For this case idf(w) = log (N/(1). The natural logarithm is used, instead of just N/df(w) to dampen the effect of idf (The natural log could be replaced by any base). If the natural log was not taken the idf would have a much greater effect than the tf on the tf-idf ranking.

The tf-idf ranking scores are printed to a file in the same directory as the program. The file is named `searchScores.txt` and it will contain the filename:score for your query on each document in descending order (delimited by new lines).

## Hashmap Implementation
Hashmaps are an efficiently searchable organization of data. The hashmap implemented here contains a linked list of words with a linked list of documents containing that word coming off of each word node. The hashing function sums the ascii values of each character in a word and uses this value (mod num buckets) to place words in their respective buckets.

<img src="images/hashmap.png">
Figure 1. Diagram of hashmap containing linked lists of linked lists.


```
// defines hashmap struct
struct hashmap {
        struct wordNode** pointerArray;
        int num_buckets;
        int numFiles;
        char** fileNames;
};

// defines word linked list struct
struct wordNode {
        char* word;
        int docFrequency;
        struct wordNode* nextWord;
        struct docNode* docList;
};

// defines document linked list struct
struct docNode {
        int docID;
        int termFrequency;
        double* tfidf;
        struct docNode* nextDoc; 
};
```
Figure 2. These struct definitions describe the structs shown in the hashmap diagram above.

### Loop Structure
When a query is searched the rank function loops through each document and then loops through each word in the search query to calculate and sum the tf-idf score for each word for each document. The documents are then sorted by score to arrive at the final ranking.


```
Rank function{

    For each document i in directory:
        For each word w in search query:
            •get linked list pointer to word node using findWord()
            •calculate tf-idf for document i word w using tfidfCalc()
            •add this tf-idf score to the sum of tf-idf scores for document i
        }
    }

    Sort array of document scores in descending order to produce final ranking
}
```
Figure 3. Loop structure for the rank() method.

## Destroy Phase Considerations  
To prevent memory leaks an exhaustive freeing of all allocated memory must be performed before the program terminates. This diagram shows the cases considered when developing code to deallocate all heap memory. Note the cases for the docNode linked list are the same as for the wordNode linked list (or for any linked list).

<img src="images/freemem.png">
Figure 4. This figure shows the considered cases when developing the freeWord() method.

## Example Input
Lets say the directory to be searched contains the following documents and the search query is “computer architecture GW”.

<img src="images/docs.png">

The hashmap data structure is created to store an inverted index of the document contents. Though not shown in the table, the frequency of a given word in a given document is stored alongside the document itself.

<img src="images/invertedIndex.png">

The search query is then represented by the occurrence counts of each word in the query. This is called the bag of words (BOW) model. The order is lost – for example, “john is quicker than mary” and “mary is quicker than john” both have the same representation in the BOW model. Thus a query of size m can be viewed as a set of m search terms/words w1, w2,...wm and the bag of words model vectorizes this query string by counting how many times each word appears in the document.

<img src="images/bagOfWords.png">

The hashmap and for loop structures described above are used to apply the BOW search phrase to the inverted index of words in documents.

### Design Tradeoff: 
1. calculate and store idf during training for each word 
2. compare docFrequency and numFiles during training

Often there will be many more words throughout the documents than there will be words in the search query. For every word that is in both the documents and the search query you require four calculations for option two. and for every word that is in the documents but not in the search query you save two calculations. Therefore, if the search query is half as long as the documents the methods are equal but as the documents grow larger than twice the search query method two becomes more efficient. 

### Weaknesses
* adding a space after the input of the search query breaks the readQuery function
* rank function currently only uses the first word in the query
* if a word appears in all documents its deleted but it should be deleted only if it shows up in the same amounts in each document
* if there is punctuation next to a word it doesn't recognize just the word (there is not partial word matching)
* empty documents might crash trainHashmap()

### Highlights 
This was really my first big C project so there were a lot of C nuances that I had to learn along the way especially in the I/O department. I Thought working with double pointers was really cool and I enjoyed creating the hashmap of lists of lists.

### Testing Instructions
To test clone the repo and `cd` into the SRC directory. Run `make` and then `./search` and folllow the prompts. The output file will be called search_scores.txt.

#### References
Some references for more information on tf-idf method for document retrieval.
* H. Wu and R. Luk and K. Wong and K. Kwok. "Interpreting TF-IDF term weights as making relevance
decisions". ACM Transactions on Information Systems, 26 (3). 2008.
* J. Ramos, “Using TF-IDF to determine word relevance in document queries”.
