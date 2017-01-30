# rgb_clustering
Fixed-radius nearest neighbours search in RGB-space

Takes as input file name as filename and distance, representing the border between clusters, as dist.  
1. Then subdivides given image's RGB-space into buckets of size dist * dist * dist.  
2. For each pixel of the image searches it's neighbours in the radius of dist inside pixel's bucket and neighbouring buckets.  
3. Resulting clusters are sorted by pixel count inside each cluster, and the first three biggest clusters are painted Red, Green, Blue respectively.  
4. Remaining clusters are painted with random color each.  
5. The resulting image representing painted clusters is saved with filename of given image plus suffix "_clusters"  
