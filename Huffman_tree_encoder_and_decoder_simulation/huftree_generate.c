#include "huftree_generate.h"

// Recursive function to print the Huffman tree
void printHuffmanTree(HuffmanNode* root,int depth){
    if(root == NULL){
        return ;
    }
    printHuffmanTree(root->right,depth+1);
    for (int i = 0; i < depth; ++i) {
        printf("\t");
    }
    printf("%c:%d\n", root->character, root->frequency);
    printHuffmanTree(root->left, depth + 1);
}


// Recursive function to encode characters
void encodeCharacters(HuffmanNode* root, char* code, int top) {
    if (root->left) {
        code[top] = '0';
        encodeCharacters(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        encodeCharacters(root->right, code, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%c", code[i]);
        }
        printf("\n");
    }
}

// Function to create a new Huffman node
HuffmanNode* createNode(char character, int frequency) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->character = character;
    node->frequency = frequency;
    node->left = node->right = NULL;
    return node;
}

// Function to create a min heap node
typedef struct {
    HuffmanNode** array; // Array of pointers to Huffman nodes
    int size;            // Current size of min heap
    int capacity;        // Capacity of min heap
} MinHeap;

// Helper function to create a min heap of given capacity
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
    return minHeap;
}

// Function to swap two min heap nodes
void swapMinHeapNode(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

// MinHeapify function
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to check if size of heap is 1
int isSizeOne(MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Function to extract minimum value node from heap
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to insert a new node to Min Heap
void insertMinHeap(MinHeap* minHeap, HuffmanNode* huffmanNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && huffmanNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = huffmanNode;
}

// Function to build a Min Heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Function to create a Min Heap of given capacity
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = createNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Function to build Huffman tree
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;

    // Step 1: Create a min heap of capacity equal to size
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Iterate while size of heap doesn't become 1
    while (!isSizeOne(minHeap)) {
        // Step 2: Extract the two minimum frequency nodes from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Step 3: Create a new internal node with frequency equal to the sum of the two nodes frequencies
        top = createNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        // Step 4: Add this node to the min heap
        insertMinHeap(minHeap, top);
    }

    // Step 5: The remaining node is the root node and the tree is complete
    return extractMin(minHeap);
}

void saveHuffmanTree(HuffmanNode* root, FILE* file, char* code, int top) {
    if (root->left) {
        code[top] = '0';
        saveHuffmanTree(root->left, file, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        saveHuffmanTree(root->right, file, code, top + 1);
    }
    if (!root->left && !root->right) {
        fprintf(file, "%c: ", root->character);
        for (int i = 0; i < top; i++) {
            fprintf(file, "%c", code[i]);
        }
        fprintf(file, "\n");
    }
}

// The main function to build Huffman Tree
HuffmanNode* generateHuffmanTree(int n) {
    char data[n];
    int freq[n];

    // Read n character
    printf("Enter %d characters (including space):\n", n);
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            scanf(" %c", &data[i]); // read a single character
        } else {
            char spaceWord[6];  // For reading the word "space"
            scanf("%s", spaceWord);
            data[i] = ' '; // Convert "space" to an actual space character
        }
    }

    // Read the frequencies of each character
    printf("Enter the frequencies of these characters:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);
    }

    // Building Huffman Tree
    HuffmanNode* root = buildHuffmanTree(data, freq, n);

    FILE* file = fopen("hfmtree", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    char code[100];
    saveHuffmanTree(root, file, code, 0);
    fclose(file);

    return root;
}

void decodeHuffmanTree(HuffmanNode* root, const char* encodedMessage) {
    HuffmanNode* current = root;
    while (*encodedMessage) {
        if (*encodedMessage == '0') {
            current = current->left;
        } else {
            current = current->right;
        }

        // 当到达叶子节点时，打印字符并重置current指针
        if (!current->left && !current->right) {
            printf("%c", current->character);
            current = root;
        }
        encodedMessage++;
    }
    printf("\n");
}