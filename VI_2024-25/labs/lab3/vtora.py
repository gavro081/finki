import os

from sklearn.preprocessing import OrdinalEncoder

os.environ['OPENBLAS_NUM_THREADS'] = '1'
# from submission_script import *
# from dataset_script import dataset
from zad2_dataset import dataset
from sklearn.naive_bayes import GaussianNB

# Ova e primerok od podatochnoto mnozestvo, za treniranje/evaluacija koristete ja
# importiranata promenliva dataset
# dataset_sample = [['1', '35', '12', '5', '1', '100', '0'],
#                   ['1', '29', '7', '5', '1', '96', '1'],
#                   ['1', '50', '8', '1', '3', '132', '0'],
#                   ['1', '32', '11.75', '7', '3', '750', '0'],
#                   ['1', '67', '9.25', '1', '1', '42', '0']]

if __name__ == '__main__':
    # Vashiot kod tuka
    classifier = GaussianNB()

    dataset = [[float(num) for num in row] for row in dataset]

    train_data = dataset[:int(0.85 * len(dataset))]
    train_X = [row[:-1] for row in train_data]
    train_Y = [row[-1] for row in train_data]

    test_data = dataset[int(0.85 * len(dataset)):]
    test_X = [row[:-1] for row in test_data]
    test_Y = [row[-1] for row in test_data]

    classifier.fit(train_X, train_Y)

    accuracy_count = 0

    for sample, rep in zip(test_X, test_Y):
        predicted = classifier.predict([sample])[0]
        if rep == predicted:
            accuracy_count += 1

    print(accuracy_count / len(test_X))

    query = [float(num) for num in input().split(" ")]

    print(int(classifier.predict([query])[0]))
    print(classifier.predict_proba([query]))


    # Na kraj potrebno e da napravite submit na podatochnoto mnozestvo,
    # klasifikatorot i encoderot so povik na slednite funkcii

    # submit na trenirachkoto mnozestvo
    # submit_train_data(train_X, train_Y)

    # submit na testirachkoto mnozestvo
    # submit_test_data(test_X, test_Y)

    # submit na klasifikatorot
    # submit_classifier(classifier)

    # povtoren import na kraj / ne ja otstranuvajte ovaa linija
