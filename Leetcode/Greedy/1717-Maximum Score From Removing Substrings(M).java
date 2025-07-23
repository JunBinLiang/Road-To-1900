class Solution {
    public int maximumGain(String s, int x, int y) {
        if(x < y) { //take ba first
            String rev = new StringBuilder(s).reverse().toString();
            return maximumGain(rev, y, x);
        }

        int ans = 0;
        Stack<Character> stk = new Stack<>();
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == 'b' && stk.size() > 0 && stk.peek() == 'a') {
                ans += x;
                stk.pop();
            } else {
                stk.push(s.charAt(i));
            }
        }

        s = to(stk);
        for(int i = 0; i < s.length(); i++) {
            if(s.charAt(i) == 'a' && stk.size() > 0 && stk.peek() == 'b') {
                ans += y;
                stk.pop();
            } else {
                stk.push(s.charAt(i));
            }
        }

        return ans;
    }

    public String to(Stack<Character> stk) {
        StringBuilder str = new StringBuilder();
        while(stk.size() > 0) str.append(stk.pop());
        return str.reverse().toString();
    }
}
