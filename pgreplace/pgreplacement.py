import queue

def fifo(pages, frame_size):
    current = set()
    q = []
    n = len(pages)
    page_fault = 0
    hits = 0
    for i in range(n):
        print(pages[i], end=" ")
        if len(current)<frame_size:
            if pages[i] not in current:
                page_fault+=1
                current.add(pages[i])
                q.append(pages[i])
                print("MISS", end=" ")
            else:
                print("HIT", end=" ")
                hits+=1
        else:
            if pages[i] not in current:
                el = q[0]
                q.pop(0)
                current.remove(el)
                current.add(pages[i])
                q.append(pages[i])
                page_fault+=1
                print("MISS", end=" ")
            else:
                print("HIT", end=" ")
                hits+=1
        print("Current queue: ",q)
    return (hits/page_fault)*100

def lru(pages, frame_size):
    current=set()
    indexes = {}
    n=len(pages)
    page_fault = 0
    hits =0
    for i in range(n):
        print(pages[i], end=" ")
        if len(current)<frame_size:
            if pages[i] not in current:
                current.add(pages[i])
                page_fault+=1
                indexes[pages[i]]=i
                print("MISS", end=" ")
            else:
                indexes[pages[i]]=i
                print("HIT", end=" ")
                hits+=1
        else:
            if pages[i] not in current:
                page_fault+=1
                least = float('inf')
                least_el = -1
                for page, ind in indexes.items():
                    if ind<least:
                        least = ind
                        least_el=page
                
                current.remove(least_el)
                current.add(pages[i])
                del indexes[least_el]
                indexes[pages[i]]=i
                print("MISS", end=" ")
            else:
                indexes[pages[i]]=i
                print("HIT", end=" ")
                hits+=1
        print("Current pages: ", current)
    return (hits/page_fault)*100

def optimal_pr(pages, frame_size):
    current = set()
    curr_pages = {}
    page_fault=0
    n=len(pages)
    hits=0
    for i in range(n):
        print(pages[i], end=" ")
        if len(current)< frame_size:
            if pages[i] not in current:
                curr_pages[pages[i]]=i
                current.add(pages[i])
                page_fault+=1
                print("MISS", end=" ")
            else:
                curr_pages[pages[i]]=i
                print("HIT", end=" ")
                hits+=1
        else:
            if pages[i] not in current:
                least = float('-inf')
                least_el = 0
                for el, index in curr_pages.items():
                    next_index = -1
                    for j in range(index+1, n):
                        if pages[j]==el:
                            next_index=j
                            break      
                   
                    if next_index==-1:
                        least_el=el
                        break
                    if next_index>least:
                        least=next_index
                        least_el=el
                current.remove(least_el)
                current.add(pages[i])
                del curr_pages[least_el]
                curr_pages[pages[i]]=i
                page_fault+=1
                print("MISS", end=" ")
            else:
                print("HIT", end=" ")
                curr_pages[pages[i]]=i
                hits+=1
        print("Current pages: ", current)
        
    return (hits/page_fault)*100

while True:
    print("\nEnter pages: ")
    pages = list(input().split(' '))
    print("Enter frame size: ")
    frame_size = int(input())

    print(f"\n\n------------------FIFO-----------------")
    f = fifo(pages,frame_size)
    print(f"\n\n------------------LRU-----------------")
    l = lru(pages, frame_size)
    print(f"\n\n------------------OPTIMAL-----------------")
    o = optimal_pr(pages, frame_size)

    print("\nFIFO hits/miss ratio: ", "{:.2f}".format(f))
    print("\nLRU hits/miss ration: ", "{:.2f}".format(l))
    print("\nOptimal hits/miss ratio: ", "{:.2f}".format(o))

    print("\nPress 1 to continue, 0 to exit")
    op=int(input())
    if op==0:
        break
