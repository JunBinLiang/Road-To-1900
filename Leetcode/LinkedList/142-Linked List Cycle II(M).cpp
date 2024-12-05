/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == NULL) return nullptr;
        ListNode* slow = head;
        ListNode* fast = head;
        if(fast == NULL) return nullptr;
        while(fast != NULL) {
            slow = slow -> next;
            fast = fast -> next;
            if(fast != NULL) fast = fast -> next;
            if(slow == fast) break;
        }
        if(slow != fast || slow == NULL) {
            return nullptr;
        }
        //length of the cycle
        ListNode* cur = head;
        while(cur != fast) {
            cur = cur -> next;
            fast = fast -> next;
        }
        return cur;
    }
};
