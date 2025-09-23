struct Interval {
    int start_time;
    int end_time;
    struct Interval *next;
    struct Interval *prev;
} Interval;


typedef struct {
	struct Interval* interval_list;
	int size;  
} MyCalendar;


struct Interval* createInterval(int start, int end) {
	
	struct Interval* interval = (struct Interval *) malloc(sizeof(struct Interval));
	if (interval == NULL)
		return NULL;
	
	interval->start_time = start;
	interval->end_time = end;
    interval->next = NULL;
    interval->prev = NULL;
	return interval;
}


bool addIntervalNextTo(struct Interval *cur_interval, struct Interval *new_interval) {
	
	if (!cur_interval->next) {
		cur_interval->next = new_interval;
		new_interval->prev = cur_interval;
	} else {
		new_interval->next = cur_interval->next;
		new_interval->prev = cur_interval;
		cur_interval->next->prev = new_interval;
		cur_interval->next = new_interval;
	}
	return true;	
}

struct Interval* findPlace(struct Interval *intervals, int startTime, int endTime) {
	struct Interval* cur_node = intervals;
	while (cur_node) {
		if (cur_node->end_time <= startTime && !cur_node->next || cur_node->next && cur_node->next->start_time >= endTime) {
			return cur_node;
		}
		cur_node = cur_node->next;
	}
	return cur_node;
}


MyCalendar* myCalendarCreate() {
    MyCalendar *calendar_inst = (MyCalendar*) malloc(sizeof(MyCalendar));
    
	if (calendar_inst == NULL)
		return NULL;
	calendar_inst->interval_list = NULL;
    calendar_inst->size = 0;
	return calendar_inst;
}

bool myCalendarBook(MyCalendar* obj, int startTime, int endTime) {
    if (!obj) return false;
    if (!obj->interval_list) {
		struct Interval *new_interval = createInterval(startTime, endTime);
		obj->interval_list = new_interval;
		obj->size++;
		return true;
	}
	
	struct Interval *next_to = findPlace(obj->interval_list, startTime, endTime);
	if (next_to) {
		struct Interval *new_interval = createInterval(startTime, endTime);
		addIntervalNextTo(next_to, new_interval);
        obj->size++;
		return true;
	} else 
		return false;
	
}

void myCalendarFree(MyCalendar* obj) {
    
}

/**
 * Your MyCalendar struct will be instantiated and called as such:
 * MyCalendar* obj = myCalendarCreate();
 * bool param_1 = myCalendarBook(obj, startTime, endTime);
 
 * myCalendarFree(obj);
*/