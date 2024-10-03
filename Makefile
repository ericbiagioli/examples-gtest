.DEFAULT_GOAL := help

.PHONY: help build

O_EXAMPLE=example-list/list
CC_EXAMPLE=example-list/list.cc example-list/list-test.cc

O_HW1=hw1/hw1
CC_HW1=hw1/hw1-test.cc

help: ## Display available commands in Makefile
	@grep -hE '^[a-zA-Z_0-9-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

buildimage: ## Build the docker image that will be used to compile and test the files
	docker build . -f Dockerfile-aed -t ubuntu-aed:1 --build-arg uid=$(shell id -u) --build-arg gid=$(shell id -g) --build-arg user=dockeruser --build-arg group=dockergroup

shell: ## Launch a bash attached to the docker image that already contains GTest and the tools needed to build the code
	docker build . -f Dockerfile-aed -t ubuntu-aed:1 --build-arg uid=$(shell id -u) --build-arg gid=$(shell id -g) --build-arg user=dockeruser --build-arg group=dockergroup
	docker run -v $(shell pwd):/workdir -w /workdir -it ubuntu-aed:1 bash

test-example: ## Compile and test the example present in the directory list
	docker build . -f Dockerfile-aed -t ubuntu-aed:1 --build-arg uid=$(shell id -u) --build-arg gid=$(shell id -g) --build-arg user=dockeruser --build-arg group=dockergroup
	echo "compiling..."
	docker run -v $(shell pwd):/workdir -w /workdir -it ubuntu-aed:1 g++ -o $(O_EXAMPLE) $(CC_EXAMPLE) -l gtest -lgtest_main -pthread
	echo "testing"
	docker run -v $(shell pwd):/workdir -w /workdir -it ubuntu-aed:1 ./$(O_EXAMPLE)

test-hw1: ## Compile and test the hw1
	docker build . -f Dockerfile-aed -t ubuntu-aed:1 --build-arg uid=$(shell id -u) --build-arg gid=$(shell id -g) --build-arg user=dockeruser --build-arg group=dockergroup
	echo "compiling..."
	docker run -v $(shell pwd):/workdir -w /workdir -it ubuntu-aed:1 g++ -o $(O_HW1) $(CC_HW1) -l gtest -lgtest_main -pthread
	echo "testing"
	docker run -v $(shell pwd):/workdir -w /workdir -it ubuntu-aed:1 ./$(O_HW1)

clean:
	rm -rf $(O_EXAMPLE) $(O_HW1)
