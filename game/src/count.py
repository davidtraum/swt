import os

total = 0

def countFile(path):
  count = 0
  with open(path) as file:
    for line in file:
      count+=1
  return count

server = 0

for file in os.listdir('server'):
  if('.py' in file and not '.pyc' in file):
    server += countFile('server/' + file)

print("Zeilen Server: ", server)

client = 0
for file in os.listdir('application_server'):
  if('.cpp' in file or '.h' in file):
    client+=countFile('application_server/' + file)

print("Zeilen Client: ", client)
total = client+server
print("Total: ", total, "Zeilen")
print("Anteil Client: ", (client/total)*100, "%, Server: ", (server/total)*100, "%")
  
