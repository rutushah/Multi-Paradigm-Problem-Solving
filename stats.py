import statistics

class StatisticsCalculator:
    def __init__(self, data: list[int]):
        self.data = data

    def report(self) -> None:
        print(f"Data:   {self.data}")
        print(f"Mean:", statistics.mean(self.data))
        print(f"Median: ", statistics.median(self.data))
        print(f"Mode:   ", statistics.mode(self.data))


if __name__ == "__main__":
    calc = StatisticsCalculator([4, 1, 2, 2, 3, 5, 3, 3, 7, 1])
    calc.report()
