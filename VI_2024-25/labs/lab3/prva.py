import os

os.environ['OPENBLAS_NUM_THREADS'] = '1'
# from submission_script import *
# from dataset_script import dataset
from zad1_dataset import dataset
from sklearn.naive_bayes import CategoricalNB
from sklearn.preprocessing import OrdinalEncoder

# Ova e primerok od podatochnoto mnozestvo, za treniranje/evaluacija koristete ja
# importiranata promenliva dataset
# dataset_sample = [['C', 'S', 'O', '1', '2', '1', '1', '2', '1', '2', '0'],
#                   ['D', 'S', 'O', '1', '3', '1', '1', '2', '1', '2', '0'],
#                   ['C', 'S', 'O', '1', '3', '1', '1', '2', '1', '1', '0'],
#                   ['D', 'S', 'O', '1', '3', '1', '1', '2', '1', '2', '0'],
#                   ['D', 'A', 'O', '1', '3', '1', '1', '2', '1', '2', '0']]

if __name__ == '__main__':
    # dataset = dataset

    encoder = OrdinalEncoder()
    classifier = CategoricalNB()

    encoder.fit([row[:-1] for row in dataset])

    train_data = dataset[:int(0.75 * len(dataset))]
    train_x = [row[:-1] for row in train_data]
    train_y = [row[-1] for row in train_data]

    test_data = dataset[int(0.75 * len(dataset)):]
    test_x = [row[:-1] for row in test_data]
    test_y = [row[-1] for row in test_data]

    train_x_encoded = encoder.transform(train_x)
    test_x_encoded = encoder.transform(test_x)

    classifier.fit(train_x_encoded, train_y)

    accuracy_count = 0

    for sample, rep in zip(test_x_encoded, test_y):
        predicted = classifier.predict([sample])[0]
        if rep == predicted:
            accuracy_count += 1

    accuracy = accuracy_count / len(test_x)
    print(accuracy)

    query = input().split(' ')
    query = encoder.transform([query])
    print(classifier.predict(query)[0])
    print(classifier.predict_proba(query))




    # Na kraj potrebno e da napravite submit na podatochnoto mnozestvo,
    # klasifikatorot i encoderot so povik na slednite funkcii

    # submit na trenirachkoto mnozestvo
    # submit_train_data(train_x_encoded, train_y)

    # submit na testirachkoto mnozestvo
    # submit_test_data(test_x_encoded, test_y)

    # submit na klasifikatorot
    # submit_classifier(classifier)

    # submit na encoderot
    # submit_encoder(encoder)
