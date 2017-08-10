package cc.arrizo.wdc.keyvalue;

import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.TextView;

import cc.arrizo.wdc.R;

public class KeyValueHolder extends RecyclerView.ViewHolder implements View.OnClickListener {

    private TextView textViewKey;
    private TextView textViewValue;
    private KeyValueListener listener;
    private KeyValueBean bean;

    public KeyValueHolder(View v, KeyValueListener listener) {
        super(v);

        this.textViewKey = (TextView) v.findViewById(R.id.textViewKey);
        this.textViewValue = (TextView) v.findViewById(R.id.textViewValue);
        this.listener = listener;

        v.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
//        listener.onClick(getAdapterPosition());
        listener.onClick(bean);
    }

    public void onBind(KeyValueBean bean) {
        this.bean = bean;
        this.textViewKey.setText(bean.getKey());
        this.textViewValue.setText(bean.getValue());
    }
}