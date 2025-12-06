import os

os.environ['OPENBLAS_NUM_THREADS'] = '1'

# from dataset_script import dataset
import math
from sklearn.naive_bayes import GaussianNB, CategoricalNB
from sklearn.preprocessing import MinMaxScaler


def main():
    global dataset

    classifier = GaussianNB()

    C = int(input())
    P = int(input())

    new_dataset = []
    for row in dataset:
        first = float(row[0]) + float(row[-2])
        new_dataset.append([first] + row[1:-2] + [row[-1]])

    dataset = new_dataset

    good = [row for row in dataset if row[-1] == "good"]
    bad = [row for row in dataset if row[-1] == "bad"]

    train_size_good = len(good) * P / 100
    train_size_bad = len(bad) * P / 100

    training_data = good[:int(train_size_good)] + bad[:int(train_size_bad)]
    testing_data = good[int(train_size_good):] + bad[int(train_size_bad):]

    if C == 1:
        train_size_good = math.ceil(len(good) * P / 100)
        train_size_bad = math.ceil(len(bad) * P / 100)
        training_data = good[-int(train_size_good):] + bad[-int(train_size_bad):]
        testing_data = good[:-int(train_size_good)] + bad[:-int(train_size_bad)]

    train_x = [row[:-1] for row in training_data]
    train_y = [row[-1] for row in training_data]

    test_x = [row[:-1] for row in testing_data]
    test_y = [row[-1] for row in testing_data]

    classifier.fit(train_x, train_y)
    score1 = classifier.score(test_x, test_y)

    scaler = MinMaxScaler(feature_range=(-1, 1))
    scaler.fit(train_x)
    train_x = scaler.transform(train_x)
    test_x = scaler.transform(test_x)

    classifier.fit(train_x, train_y)
    score2 = classifier.score(test_x, test_y)

    print(f"Broj na podatoci vo train se: {len(train_x)}")
    print(f"Broj na podatoci vo test se: {len(test_x)}")
    print(f"Tochnost so zbir na koloni: {score1}")
    print(f"Tochnost so zbir na koloni i skaliranje: {score2}")


main()