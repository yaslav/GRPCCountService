from concurrent import futures
import grpc
import counter_pb2_grpc
import counter_pb2
import time
import threading


def runClient():
    counter = 0
    with grpc.insecure_channel("localhost:4567") as channel:
        stub = counter_pb2_grpc.CountServiceStub(channel)
        while True:
            response = stub.sendRequest(counter_pb2.CountRequest(count=counter))
            counter = response.count
            time.sleep(0.01)
            print(counter)

if __name__ == "__main__":
    runClient()

