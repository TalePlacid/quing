#include "Test_ChildArrayForest.h"
#include "../../../ChildArrayForest.h"
#include "../Local8BitStringConverter.h"
#include "../AssertReporter.h"

#pragma warning(disable:4996)

Test_ChildArrayForest::Test_ChildArrayForest(){

}

Test_ChildArrayForest::~Test_ChildArrayForest(){

}

void Test_ChildArrayForest::Execute(){
    ChildArrayForest<Int> childArrayForest;

    // 1. 기본 트리를 구성한다.
    ChildArrayForest<Int>::Node* node10 = childArrayForest.Insert(10);
    ChildArrayForest<Int>::Node* node20 = childArrayForest.Insert(20);
    ChildArrayForest<Int>::Node* node30 = childArrayForest.Insert(30);
    ChildArrayForest<Int>::Node* node100 = childArrayForest.Insert(node10, 100);
    ChildArrayForest<Int>::Node* node110 = childArrayForest.Insert(node10, 110);
    ChildArrayForest<Int>::Node* node1000 = childArrayForest.Insert(node100, 1000);
    ChildArrayForest<Int>::Node* node200 = childArrayForest.Insert(node20, 200);
    ChildArrayForest<Int>::Node* node2000 = childArrayForest.Insert(node200, 2000);
    ChildArrayForest<Int>::Node* node2010 = childArrayForest.Insert(node200, 2010);
    ChildArrayForest<Int>::Node* node300 = childArrayForest.Insert(node30, 300);
    ChildArrayForest<Int>::Node* node310 = childArrayForest.Insert(node30, 310);
    ChildArrayForest<Int>::Node* node3100 = childArrayForest.Insert(node310, 3100);
    ChildArrayForest<Int>::Node* node3110 = childArrayForest.Insert(node310, 3110);
    ChildArrayForest<Int>::Node* node3120 = childArrayForest.Insert(node310, 3120);

    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node10) == vector<ChildArrayForest<Int>::OrderEntry>({{10, 0}, {100, 1}, {1000, 2}, {110, 1}}),
                           Local8BitStringConverter::Convert("10 서브트리 구성 테스트 실패"));
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node20) == vector<ChildArrayForest<Int>::OrderEntry>({{20, 0}, {200, 1}, {2000, 2}, {2010, 2}}),
                           Local8BitStringConverter::Convert("20 서브트리 구성 테스트 실패"));
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node30) == vector<ChildArrayForest<Int>::OrderEntry>({{30, 0}, {300, 1}, {310, 1}, {3100, 2}, {3110, 2}, {3120, 2}}),
                           Local8BitStringConverter::Convert("30 서브트리 구성 테스트 실패"));

    // 2. 복사 생성한다.
    ChildArrayForest<Int> copy(childArrayForest);
    ChildArrayForest<Int>::Node* copyNode10 = copy.Search(static_cast<Int>(10), this->MatchInt);
    ChildArrayForest<Int>::Node* copyNode20 = copy.Search(static_cast<Int>(20), this->MatchInt);
    ChildArrayForest<Int>::Node* copyNode30 = copy.Search(static_cast<Int>(30), this->MatchInt);
    AssertReporter::Assert(copy.GetPreOrderEntries(copyNode10) == vector<ChildArrayForest<Int>::OrderEntry>({{10, 0}, {100, 1}, {1000, 2}, {110, 1}})
                   && copy.GetPreOrderEntries(copyNode20) == vector<ChildArrayForest<Int>::OrderEntry>({{20, 0}, {200, 1}, {2000, 2}, {2010, 2}})
                   && copy.GetPreOrderEntries(copyNode30) == vector<ChildArrayForest<Int>::OrderEntry>({{30, 0}, {300, 1}, {310, 1}, {3100, 2}, {3110, 2}, {3120, 2}}),
                           Local8BitStringConverter::Convert("복사생성자 테스트 실패"));

    // 3. 삭제한다.
    ChildArrayForest<Int>::Node* searchedNode = childArrayForest.Search(static_cast<Int>(3110), this->MatchInt);
    AssertReporter::Assert(searchedNode == node3110,
                           Local8BitStringConverter::Convert("3110 검색 테스트 실패"));

    childArrayForest.Delete(searchedNode);
    AssertReporter::Assert(childArrayForest.Search(static_cast<Int>(3110), this->MatchInt) == 0
                   && childArrayForest.GetPreOrderEntries(node310) == vector<ChildArrayForest<Int>::OrderEntry>({{310, 0}, {3100, 1}, {3120, 1}}),
                           Local8BitStringConverter::Convert("3110 삭제 테스트 실패"));

    AssertReporter::Assert(childArrayForest.Search(static_cast<Int>(4000), this->MatchInt) == 0,
                           Local8BitStringConverter::Convert("4000 검색 실패 테스트 실패"));

    searchedNode = childArrayForest.Search(static_cast<Int>(200), this->MatchInt);
    AssertReporter::Assert(searchedNode == node200,
                           Local8BitStringConverter::Convert("200 검색 테스트 실패"));

    childArrayForest.Delete(searchedNode);
    AssertReporter::Assert(childArrayForest.Search(static_cast<Int>(200), this->MatchInt) == 0
                   && childArrayForest.Search(static_cast<Int>(2000), this->MatchInt) == 0
                   && childArrayForest.Search(static_cast<Int>(2010), this->MatchInt) == 0
                   && childArrayForest.GetPreOrderEntries(node20) == vector<ChildArrayForest<Int>::OrderEntry>({{20, 0}}),
                           Local8BitStringConverter::Convert("200 서브트리 삭제 테스트 실패"));

    // 4. 루트 노드의 순서를 변경한다.
    ChildArrayForest<Int>::Node* node5 = childArrayForest.Insert(5);
    childArrayForest.MoveNode(node5, 0);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(0) == vector<ChildArrayForest<Int>::OrderEntry>({{5, 0}, {10, 0}, {100, 1}, {1000, 2}, {110, 1}, {20, 0}, {30, 0}, {300, 1}, {310, 1}, {3100, 2}, {3120, 2}}),
                           Local8BitStringConverter::Convert("5 루트 이동 테스트 실패"));

    ChildArrayForest<Int>::Node* node15 = childArrayForest.Insert(15);
    childArrayForest.MoveNode(node15, 2);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(0) == vector<ChildArrayForest<Int>::OrderEntry>({{5, 0}, {10, 0}, {100, 1}, {1000, 2}, {110, 1}, {15, 0}, {20, 0}, {30, 0}, {300, 1}, {310, 1}, {3100, 2}, {3120, 2}}),
                           Local8BitStringConverter::Convert("15 루트 이동 테스트 실패"));

    // 5. 자식 노드의 순서를 변경한다.
    searchedNode = childArrayForest.Search(static_cast<Int>(3120), this->MatchInt);
    AssertReporter::Assert(searchedNode == node3120,
                           Local8BitStringConverter::Convert("3120 검색 테스트 실패"));

    node310->MoveNode(node3120, 0);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node310) == vector<ChildArrayForest<Int>::OrderEntry>({{310, 0}, {3120, 1}, {3100, 1}}),
                           Local8BitStringConverter::Convert("310 자식 재정렬 테스트 실패"));

    searchedNode = childArrayForest.Search(static_cast<Int>(310), this->MatchInt);
    AssertReporter::Assert(searchedNode == node310,
                           Local8BitStringConverter::Convert("310 검색 테스트 실패"));

    searchedNode = childArrayForest.Search(static_cast<Int>(5), this->MatchInt);
    AssertReporter::Assert(searchedNode == node5,
                           Local8BitStringConverter::Convert("5 검색 테스트 실패"));

    childArrayForest.MoveAsChild(node310, node5, 0);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node5) == vector<ChildArrayForest<Int>::OrderEntry>({{5, 0}, {310, 1}, {3120, 2}, {3100, 2}})
                   && childArrayForest.GetPreOrderEntries(node30) == vector<ChildArrayForest<Int>::OrderEntry>({{30, 0}, {300, 1}}),
                           Local8BitStringConverter::Convert("310을 5의 자식으로 이동 테스트 실패"));

    searchedNode = childArrayForest.Search(static_cast<Int>(15), this->MatchInt);
    AssertReporter::Assert(searchedNode == node15,
                           Local8BitStringConverter::Convert("15 검색 테스트 실패"));

    childArrayForest.MoveAsChild(node5, node15, 0);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node15) == vector<ChildArrayForest<Int>::OrderEntry>({{15, 0}, {5, 1}, {310, 2}, {3120, 3}, {3100, 3}}),
                           Local8BitStringConverter::Convert("5를 15의 자식으로 이동 테스트 실패"));

    searchedNode = childArrayForest.Search(static_cast<Int>(15), this->MatchInt);
    AssertReporter::Assert(searchedNode == node15,
                           Local8BitStringConverter::Convert("이동 후 15 검색 테스트 실패"));

    // 6. 수정한다.
    childArrayForest.Update(node15, 500);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node15) == vector<ChildArrayForest<Int>::OrderEntry>({{500, 0}, {5, 1}, {310, 2}, {3120, 3}, {3100, 3}}),
                           Local8BitStringConverter::Convert("500 수정 테스트 실패"));

    // 7. 순회 연산한다.
    childArrayForest.ForEachPostOrder(0, this->AddOne);
    AssertReporter::Assert(childArrayForest.GetPreOrderEntries(node15) == vector<ChildArrayForest<Int>::OrderEntry>({{501, 0}, {6, 1}, {311, 2}, {3121, 3}, {3101, 3}})
                   && childArrayForest.GetPreOrderEntries(node20) == vector<ChildArrayForest<Int>::OrderEntry>({{21, 0}})
                   && childArrayForest.GetPreOrderEntries(node30) == vector<ChildArrayForest<Int>::OrderEntry>({{31, 0}, {301, 1}}),
                           Local8BitStringConverter::Convert("ForEachPostOrder 테스트 실패"));

    // 8. 치환한다.
    copy = childArrayForest;
    copyNode10 = copy.Search(static_cast<Int>(11), this->MatchInt);
    ChildArrayForest<Int>::Node* copyNode15 = copy.Search(static_cast<Int>(501), this->MatchInt);
    copyNode20 = copy.Search(static_cast<Int>(21), this->MatchInt);
    copyNode30 = copy.Search(static_cast<Int>(31), this->MatchInt);
    AssertReporter::Assert(copy.GetPreOrderEntries(copyNode10) == vector<ChildArrayForest<Int>::OrderEntry>({{11, 0}, {101, 1}, {1001, 2}, {111, 1}})
                   && copy.GetPreOrderEntries(copyNode15) == vector<ChildArrayForest<Int>::OrderEntry>({{501, 0}, {6, 1}, {311, 2}, {3121, 3}, {3101, 3}})
                   && copy.GetPreOrderEntries(copyNode20) == vector<ChildArrayForest<Int>::OrderEntry>({{21, 0}})
                   && copy.GetPreOrderEntries(copyNode30) == vector<ChildArrayForest<Int>::OrderEntry>({{31, 0}, {301, 1}}),
                           Local8BitStringConverter::Convert("치환연산 테스트 실패"));
}

bool Test_ChildArrayForest::MatchInt(const Int& object, const Int& key){
    return object == key;
}

void Test_ChildArrayForest::AddOne(Int& element){
    element++;
}

string Test_ChildArrayForest::GetName(){
    return "Test_ChildArrayForest";
}
