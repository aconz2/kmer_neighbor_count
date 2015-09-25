# Purpose
Given a fasta file and a kmer size:
for each kmer in each contig, output the number of contigs which have that kmer.
Kmers are counted by their canonical form, a la. Jellyfish (the lesser of a kmer and its reverse complement)

# Input
A fasta file of a "2-line" format. This will not handle wrapped sequences.

# Output
A fasta-like file of a "2-line" format. That is, id on first line, and tab separated counts on the next
```
>id line printed verbatim from intput
<integer>\t<integer>\t...<integer>
```

# Requirements
 - a c++11 compiler

# Running

```
make
./kmer_neighbor_count <input_file> <kmer_length>
```
 - `<input_file>` must be a real file (reopenable)
 - `<kmer_length>` should be between 1 and 32 inclusive

