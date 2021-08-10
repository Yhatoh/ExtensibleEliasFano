import random

testCases = 1
bitLimit = 100000000
probabilities = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]

random.seed(2015735042)

#randombits
for test in range(testCases):
  for probabilitie in probabilities:
    onesCount = 0
    testFile = open(f'./randomBits/p{probabilitie}t{test}.txt', 'w')
    testFile.write(f'{bitLimit}\n')
    for bitPos in range(0, bitLimit):
      randResult = random.randint(1, 1000)
      if randResult <= probabilitie:
        bit = 1
      else:
        bit = 0
      onesCount += bit
      testFile.write(f'{bit}')
    testFile.close()
    print(f'./randomBits/p{probabilitie}t{test}.txt')
