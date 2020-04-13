struct ListNode {
	int val;
	struct ListNode* next;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* head = l1;
	struct ListNode* preL1 = l1;
	while(l1 != NULL){
	    if(l2 != NULL){
		    int sum = l1->val + l2->val;
		    l1->val = sum % 10;
	
		    if(sum >= 10){
			    if(l1->next == NULL){
				    l1->next = (struct ListNode*) malloc(sizeof(struct ListNode));
				    l1->next->next = NULL;
			    }
			    l1->next->val += sum / 10;
		    }
		    l2 = l2->next;
		    
	    }else{
	        if(l1->val >= 10){
	            if(l1->next == NULL){
				    l1->next = (struct ListNode*) malloc(sizeof(struct ListNode));
				    l1->next->next = NULL;
			    }
			    l1->next->val += l1->val / 10;
			    l1->val = l1->val % 10;
	        }
	    }
	    
	    preL1 = l1;
	    l1 = l1->next;
	}
	
	if(l1 == NULL)
		preL1->next = l2;

	return head;
}

int main(int argc, char** argv){
	return 0;
}
