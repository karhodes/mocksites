angular.module("myApp",[])
	.controller("myController", function($scope, myService){
		//$scope.test = "hi there";

		$scope.emp = {};

		$scope.itemArray = myService.getItems();

		$scope.onSave = function(){
			myService.addItems($scope.emp);
			$scope.emp = {};
		}

		$scope.removeItemAt = function(idx){
			myService.removeItemAt(idx)
		}

	})
	
	.service("myService", function(){

		var itemArray = [];

		this.getItems = function(){
			var str = localStorage.getItem("empLS");
			itemArray = JSON.parse(str) || itemArray;
			return itemArray;
		}

		this.addItems = function(pItem){
			itemArray.push(pItem);
			var str = JSON.stringify(itemArray);
			localStorage.setItem("empLS",str);
		}

		this.removeItemAt = function(pIndex){
			itemArray.splice(pIndex,1);
			var str = JSON.stringify(itemArray);
			localStorage.setItem("empLS",str);
		}

	});


