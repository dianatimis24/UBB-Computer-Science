package controller;

import exceptions.MyHeapAddressNotAssociatedException;
import exceptions.MyKeyNotFoundException;
import model.state.heap.IHeap;
import model.state.symbolTable.ISymbolTable;
import model.value.ReferenceValue;
import model.value.Value;

import java.util.*;
import java.util.stream.Collectors;

public class GarbageCollector {
    public Map<Integer, Value> garbageCollector(Set<Integer> reachableAddresses, Map<Integer, Value> heap) {
        return heap.entrySet().stream()
                .filter(e -> reachableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    public Set<Integer> getReachableAddresses(List<ISymbolTable> symbolsTables, IHeap heap) {
        Set<Integer> roots = symbolsTables.stream()
                .flatMap(sym -> sym.getValues().stream())
                .filter(v -> v instanceof ReferenceValue)
                .map(v -> ((ReferenceValue) v).getAddress())
                .filter(addr -> addr != 0)
                .collect(Collectors.toSet());

        Set<Integer> reachableAddresses = new HashSet<>();
        Stack<Integer> reachableAddressesStack = new Stack<>();
        reachableAddressesStack.addAll(roots);

        while (!reachableAddressesStack.isEmpty()) {
            int address = reachableAddressesStack.pop();
            if (!reachableAddresses.add(address)) {
                continue;
            }

            Value value;
            try {
                value = heap.getValueForKey(address);
            } catch (MyKeyNotFoundException e) {
                throw new MyHeapAddressNotAssociatedException(address);
            }

            if (value instanceof ReferenceValue referenceValue) {
                int nextAddress = referenceValue.getAddress();
                if (nextAddress != 0 && !reachableAddresses.contains(nextAddress)) {
                    reachableAddressesStack.push(nextAddress);
                }
            }
        }

        return reachableAddresses;
    }
}
