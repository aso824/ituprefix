#!/usr/bin/python3

# Imports
from urllib import request		# Downloading HTML
import re						# Parsing with regex
from csv import writer			# Export data

# Address with list on ARRL website
URL = 'http://www.arrl.org/international-call-sign-series'

# Output file with parsed list
OUTFILE = 'prefixlist.csv'

# Open file
f = open(OUTFILE, "w")

# Download HTML
page = request.urlopen(URL).read().decode('utf-8')

# Create regular expression
regex = re.compile('<tr><td><strong>(.*?)</strong></td>\s*<td>(.*?)</td>\s*</tr>', re.MULTILINE)

# List
li = regex.findall(page)

# Remove first and last rows (table headers)
li = li[1:-1]

# Remove all links and non-breaking spaces
for i in range(len(li)):
	# Convert tuple to list
	lst = list(li[i])
	
	# Remove non-breaking spaces
	rep = lst[1].replace(u'\xa0', u'')
	lst.append(rep)
	
	# Remove HTML links
	lst[0] = re.sub('<.*?>', '', lst[0])
	
	# Split range to two list elements
	spl = lst[0].split('-')
	lst[0] = spl[0]
	lst[1] = spl[1]
	
	# Delete stars and spaces from first row
	lst[0] = lst[0].strip('*')
	lst[0] = lst[0].strip(' ')
	
	# Save changes to main list
	li[i] = lst

# Export data to file
wr = writer(f)

for el in li:
	wr.writerow(el)

# Close file
f.close()

# Write message
print("Exported " + str(len(li)) + " lines of data to " + OUTFILE)
