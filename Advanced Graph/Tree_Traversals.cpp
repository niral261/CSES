#include <iostream>
#include <vector>

using namespace std;

vector<int> preorder, inorder, postorder;
vector<int> in_pos;

void build_postorder(int pre_start, int pre_end, int in_start, int in_end) {
    if(pre_start > pre_end || in_start > in_end) {
        return;
    }

    int root = preorder[pre_start];
    int root_index = in_pos[root];
    int left_size = root_index - in_start;
    
    build_postorder(pre_start+1, pre_start+left_size, in_start, root_index-1);
    build_postorder(pre_start+left_size+1, pre_end, root_index+1, in_end);

    postorder.push_back(root);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    preorder.resize(n);
    inorder.resize(n);
    in_pos.resize(n+1);

    for(int i=0;i<n;i++) {
        cin >> preorder[i];
    }

    for(int i=0;i<n;i++) {
        cin >> inorder[i];
        in_pos[inorder[i]] = i;
    }

    build_postorder(0,n-1,0,n-1);

    for (int i = 0; i < n; ++i) {
        cout << postorder[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}