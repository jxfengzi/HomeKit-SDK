package cc.arrizo.wdc.keyvalue;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.util.TypedValue;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;
import java.util.List;

import cc.arrizo.wdc.R;

public class KeyValueAdapter extends RecyclerView.Adapter<KeyValueHolder> {

    private List<KeyValueBean> list = new ArrayList<>();
    private KeyValueListener listener;
    private final int mBackground;
    private final TypedValue mTypedValue = new TypedValue();

    public KeyValueAdapter(Context context, KeyValueListener listener) {
        this.listener = listener;
        context.getTheme().resolveAttribute(R.attr.selectableItemBackground, mTypedValue, true);
        mBackground = mTypedValue.resourceId;
    }

    @Override
    public KeyValueHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View v = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_keyvalue, parent, false);
        v.setBackgroundResource(mBackground);

        return new KeyValueHolder(v, listener);
    }

    @Override
    public void onBindViewHolder(KeyValueHolder holder, int position) {
        holder.onBind(list.get(position));
    }

    @Override
    public int getItemCount() {
        return list.size();
    }

    public List<KeyValueBean> getList() {
        return list;
    }
}