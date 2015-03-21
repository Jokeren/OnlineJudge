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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        ListNode* p = head;
        ListNode* q = head;

        int i = 0;
        for (; i < n; i++) {
            p = p->next;
        }
        
        while (p != NULL && p->next != NULL) {
            p = p->next;
            q = q->next;
        }
        
        if (p == NULL) {
            return head = head->next;
        }
        
        q->next = q->next->next;
        return head;
    }
};